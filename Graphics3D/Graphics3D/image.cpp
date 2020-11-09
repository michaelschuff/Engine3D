//
//  image.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "image.hpp"

image::image() : data(1, new color()), m_width(1), m_height(1) {
    
}

image::image(const std::string& file_path) {
    loadImage(file_path);
}

image::image(const color& t_c) : data(1, new color(t_c)), m_width(1), m_height(1) {
    
}

image::image(const color& t_c,
             const unsigned int& t_width,
             const unsigned int& t_height) :
             data(t_width * t_height, new color(t_c)),
             m_width(t_width),
             m_height(t_height) {
    
}

void image::loadImage(const std::string& file_path) {
    loadBMPFile(file_path);
}

color* image::get(const unsigned int& x, const unsigned int& y) {
    if (0<=x && x<m_width && 0<=y && y<m_height) {
        return data[y*m_width + x];
    } else {
        if (0<x) {
            throw std::out_of_range("Cannot get negative width index of image.");
        } else if (x >= m_width) {
            throw std::out_of_range("Cannot get width index greater than image width");
        } else if (0<y) {
            throw std::out_of_range("Cannot get negative height index of image.");
        } else if (y >= m_height) {
            throw std::out_of_range("Cannot get height index greater than image height");
        } else {
            throw std::out_of_range("Cannot get index " + std::to_string(y*m_width + x) + " of image data.");
        }
    }
}

unsigned int image::width() {
    return m_width;
}

unsigned int image::height() {
    return m_height;
}

void image::loadBMPFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (file) {
        file.read((char*) &bfh, 14);
        if (bfh.FileType != 0x4D42) {
            throw std::runtime_error("Unrecognized file format.");
        }
        
        file.read((char*) &bih, 40);
        
        if (bih.BitsPerPixel <= 8) {
            bch.ColorPallet = new unsigned char[4*bih.TotalColors];
            file.read((char*) bch.ColorPallet, 4*bih.TotalColors);
        } else if (bih.BitsPerPixel != 24) {
            file.read((char*) &bch, bih.HeaderSize - 40);
            if (bch.AlphaBitMask != 0xff000000 || bch.RedBitMask != 0x00ff0000 || bch.GreenBitMask != 0x0000ff00 || bch.BlueBitMask != 0x000000ff) {
                throw std::runtime_error("Unexpected color mask format! Expected BGRA format");
            }
            if(bch.ColorSpaceType != 0x73524742) {
                throw std::runtime_error("Unexpected color space type! Expected sRGB values");
            }
        }
        
        file.seekg(bfh.PixelDataOffset, file.beg);
        
        if (bih.ImageHeight < 0) {
            throw std::runtime_error("Haven't implemented negative height yet");
        }
        unsigned int padding = (((32 - ((bih.ImageWidth*bih.BitsPerPixel) % 32)))/8)%4;
        m_width = bih.ImageWidth;
        m_height = bih.ImageHeight;
        int num_of_pixels = bih.ImageWidth * bih.ImageHeight;
        data.resize(num_of_pixels);
        unsigned int data_size = bih.ImageHeight*padding + ceil(num_of_pixels*bih.BitsPerPixel/8.0);
        unsigned char* pixel_data = new unsigned char[data_size];
        file.read((char*) pixel_data, data_size);
        switch (bih.BitsPerPixel) {
            case 1: { // 8 pixel indices per byte, each index is 1 bit
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        for (int shift = 7; shift >= 0; shift--) {
                            if (8 * (row*bih.ImageWidth + col) < num_of_pixels) {
                                unsigned int index = row*bih.ImageWidth + col;
                                uint8_t pallet_index = pixel_data[index + row*padding]>>shift & 1;
                                data[index + 7-shift] = new color(bch.ColorPallet[4*pallet_index + 2],
                                                                  bch.ColorPallet[4*pallet_index + 1],
                                                                  bch.ColorPallet[4*pallet_index],
                                                                  COLOR_MODEL::RGB256);
                            }
                        }
                        
                    }
                }
                break;
            } case 4: { // 2 pixel indices per byte, each index is 4 bits
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        unsigned int index = row*bih.ImageWidth + col;
                        unsigned int pallet_index;
                        if (col%2 == 0) {
                            pallet_index = pixel_data[index + row*padding] >> 4;
                        } else {
                            pallet_index = pixel_data[index + row*padding] & 0b11110000;
                        }
                        data[index] = new color(bch.ColorPallet[4*pallet_index+2],
                                                bch.ColorPallet[4*pallet_index+1],
                                                bch.ColorPallet[4*pallet_index],
                                                COLOR_MODEL::RGB16);
                    }
                }
                break;
            } case 8: { // 1 pixel index per byte, each index is 8 bits
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        unsigned int index = row*bih.ImageWidth + col;
                        data[index] = new color(bch.ColorPallet[4*pixel_data[index + row*padding]+2],
                                                bch.ColorPallet[4*pixel_data[index + row*padding]+1],
                                                bch.ColorPallet[4*pixel_data[index + row*padding]+0],
                                                COLOR_MODEL::RGB256);
                    }
                }
                break;
            } case 16: { // 1 pixel per 2 bytes. 5 bits per RGB channel, 16th bit ignored
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        unsigned int index = row*bih.ImageWidth + col;
                        uint8_t char1 = pixel_data[2*index],
                                char2 = pixel_data[2*index + 1];
                        data[index] = new color(char1>>3 & 0b00011111,
                                                (char1<<2 & 0b00011100) | (char2>>6),
                                                char2>>1 & 0b00011111,
                                                COLOR_MODEL::RGB32);
                    }
                }
                break;
            } case 24: { // 1 pixel per 3 bytes. 8 bits per RGB channel
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        unsigned int index = row*bih.ImageWidth + col;
                        data[index] = new color(pixel_data[3*index + row*padding + 2],
                                                pixel_data[3*index + row*padding + 1],
                                                pixel_data[3*index + row*padding + 0],
                                                COLOR_MODEL::RGB256);
                    }
                }
                break;
            } case 32: { // 1 pixel per 4 bytes. 8 bits per RGBA channel
                for (int row = 0; row < bih.ImageHeight; row++) {
                    for (int col = 0; col < bih.ImageWidth; col++) {
                        unsigned int index = row*bih.ImageWidth + col;
                        // padding is 0
                        data[index] = new color(pixel_data[4*index + row*padding + 2],
                                                pixel_data[4*index + row*padding + 1],
                                                pixel_data[4*index + row*padding + 0],
                                                pixel_data[4*index + row*padding + 3],
                                                COLOR_MODEL::RGB256);
                    }
                }
                break;
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file " + file_path);
    }
}
