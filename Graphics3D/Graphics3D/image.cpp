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
    if (0<=x && x<info_header.ImageWidth && 0<=y && y<info_header.ImageHeight) {
        if (!isTopDown) {
            return data[y*info_header.ImageWidth + x];
        } else {
            return data[(info_header.ImageHeight-y-1)*info_header.ImageWidth + x];
        }
    } else {
        throw std::out_of_range("Image index out of bounds");
    }
}

unsigned int image::width() {
    return info_header.ImageWidth;
}

unsigned int image::height() {
    return info_header.ImageHeight;
}

void image::loadBMPFile(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (file) {
        file.read((char*) &file_header, 14);
        if (file_header.FileType != 0x4D42) {
            throw std::runtime_error("Unrecognized file format.");
        }
        uint32_t header_size;
        file.read((char*) &header_size, 4);
        file.seekg(14, file.beg);
        if (header_size == 12 || header_size == 64) {
            file.read((char*) &core_header, header_size);
            //translate Core Header to Info Header
        } else if (header_size == 40 ||
                   header_size == 52 ||
                   header_size == 56 ||
                   header_size == 108 ||
                   header_size == 124) {
            file.read((char*) &info_header, header_size);
        } else {
            throw std::runtime_error("Unrecognized header format");
        }
        info_header.ImageSize = file_header.FileSize - file_header.PixelDataOffset;
        
        
        if (info_header.BitsPerPixel <= 8) {
            if (info_header.TotalColors == 0) {
                info_header.TotalColors = 1 << info_header.BitsPerPixel;
            }
            for (int i = 0; i < info_header.TotalColors; i++) {
                char r, g, b, a;
                file.read(&b, 1);
                file.read(&g, 1);
                file.read(&r, 1);
                file.read(&a, 1);
                ColorPallet.push_back(color(r, g, b, COLOR_MODEL::RGB256));
            }
        } else if (info_header.BitsPerPixel != 24) {
            file.read((char*) &color_header, info_header.HeaderSize - header_size);
            if (color_header.AlphaBitmask != 0xff000000 || color_header.RedBitmask != 0x00ff0000 || color_header.GreenBitmask != 0x0000ff00 || color_header.BlueBitmask != 0x000000ff) {
                throw std::runtime_error("Unexpected color mask format! Expected BGRA format");
            }
            if(color_header.ColorSpaceType != 0x73524742) {
                throw std::runtime_error("Unexpected color space type! Expected sRGB values");
            }
        }
        
        file.seekg(file_header.PixelDataOffset, file.beg);
        
        if (info_header.ImageHeight < 0) {
            isTopDown = true;
            info_header.ImageHeight = std::abs(info_header.ImageHeight);
        }
        unsigned char* pixel_data = new unsigned char[info_header.ImageSize];
        file.read((char*) pixel_data, info_header.ImageSize);
        switch (info_header.Compression) {
            case 0: { // No compression
                switch (info_header.BitsPerPixel) {
                    case 1: { // 8 pixel indices per byte, each index is 1 bit
                        BMPload1bpp(pixel_data);
                        break;
                    } case 4: { // 2 pixel indices per byte, each index is 4 bits
                        BMPload4bpp(pixel_data);
                        break;
                    } case 8: { // 1 pixel index per byte, each index is 8 bits
                        BMPload8bpp(pixel_data);
                        break;
                    } case 16: { // 1 pixel per 2 bytes. 5 bits per RGB channel, 16th bit ignored
                        BMPload16bpp(pixel_data);
                        break;
                    } case 24: { // 1 pixel per 3 bytes. 8 bits per RGB channel
                        BMPload24bpp(pixel_data);
                        break;
                    } case 32: { // 1 pixel per 4 bytes. 8 bits per RGBA channel
                        BMPload32bpp(pixel_data);
                        break;
                    }
                }
                break;
            } case 1: { // 8-bpp RLE
                BMPload8bppRLECompression(pixel_data);
                break;
            } case 2: { // 4-bpp RLE
                BMPload4bppRLECompression(pixel_data);
                break;
            }
        }
        file.close();
        std::cout << "Successfully loaded bmp file " + file_path.substr(74, file_path.size() - 74) << std::endl;
    } else {
        throw std::runtime_error("Unable to open file " + file_path);
    }
}

void image::BMPload1bpp(const unsigned char* pixel_data) {
    unsigned int padding = (4 - (((int) ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0))%4))%4;
    unsigned int pallet_index;
    unsigned int row_width = ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0) + padding;
    for (int i = 0; i < info_header.ImageSize; i++) {
        for (int shift = 0; shift < 8; shift++) {
            if (8*(i%row_width) + shift < info_header.ImageWidth) {
                pallet_index = pixel_data[i]>>((8-1) - 1*shift) & 0b00000001;
                data.push_back(&ColorPallet[pallet_index]);
            }
        }
    }
}

void image::BMPload4bpp(const unsigned char* pixel_data) {
    unsigned int padding = (4 - (((int) ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0))%4))%4;
    unsigned int pallet_index;
    unsigned int row_width = ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0) + padding;
    for (int i = 0; i < info_header.ImageSize; i++) {
        for (int shift = 0; shift < 2; shift++) {
            if (2*(i%row_width) + shift < info_header.ImageWidth) {
                pallet_index = pixel_data[i]>>((8-4) - 4*shift) & 0b00001111;
                data.push_back(&ColorPallet[pallet_index]);
            }
        }
    }
}

void image::BMPload8bpp(const unsigned char* pixel_data) {
    unsigned int padding = (4 - (((int) ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0))%4))%4;
    unsigned int row_width = ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0) + padding;
    for (int i = 0; i < info_header.ImageSize; i++) {
        if (i%row_width < info_header.ImageWidth) {
            data.push_back(&ColorPallet[pixel_data[i]]);
        }
    }
}

void image::BMPload16bpp(const unsigned char* pixel_data) {
    for (int row = 0; row < info_header.ImageHeight; row++) {
        for (int col = 0; col < info_header.ImageWidth; col++) {
            unsigned int index = row*info_header.ImageWidth + col;
            uint8_t char1 = pixel_data[2*index];
            uint8_t char2 = pixel_data[2*index + 1];
            data.push_back(new color( char1>>3 & 0b00011111,
                                     (char1<<2 & 0b00011100) | (char2>>6),
                                      char2>>1 & 0b00011111,
                                     COLOR_MODEL::RGB32));
        }
    }
}

void image::BMPload24bpp(const unsigned char* pixel_data) {
    unsigned int padding = (4 - (((int) ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0))%4))%4;
    for (int row = 0; row < info_header.ImageHeight; row++) {
        for (int col = 0; col < info_header.ImageWidth; col++) {
            unsigned int index = row*info_header.ImageWidth + col;
            data.push_back(new color(pixel_data[3*index + row*padding + 2],
                                     pixel_data[3*index + row*padding + 1],
                                     pixel_data[3*index + row*padding + 0],
                                     COLOR_MODEL::RGB256));
        }
    }
}

void image::BMPload32bpp(const unsigned char* pixel_data) {
    unsigned int padding = (4 - (((int) ceil(info_header.ImageWidth*info_header.BitsPerPixel/8.0))%4))%4;
    for (int row = 0; row < info_header.ImageHeight; row++) {
        for (int col = 0; col < info_header.ImageWidth; col++) {
            unsigned int index = row*info_header.ImageWidth + col;
            // padding is 0
            data.push_back(new color(pixel_data[4*index + row*padding + 2],
                                     pixel_data[4*index + row*padding + 1],
                                     pixel_data[4*index + row*padding + 0],
                                     pixel_data[4*index + row*padding + 3],
                                     COLOR_MODEL::RGB256));
        }
    }
}

void image::BMPload4bppRLECompression(const unsigned char* pixel_data) {
    unsigned int i = 0;
    while (i < info_header.ImageSize) {
        unsigned int escape = pixel_data[i];
        if (escape != 0) { // if not an escape byte
            color* c1 = &ColorPallet[pixel_data[i+1] >> 4];
            color* c2 = &ColorPallet[pixel_data[i+1] & 0b00001111];
            for (int j = 0; j < escape; j++) {
                if (j%2 == 0) {
                    data.push_back(c1);
                } else {
                    data.push_back(c2);
                }
            }
        } else {
            switch (pixel_data[i+1]) {
                case 0: { // Escape code for end of line
                    while (data.size() % info_header.ImageWidth != 0) {
                        data.push_back(&ColorPallet[0]);
                    }
                    break;
                } case 1: { // Escape code for end of bitmap
                    while (data.size() < m_width*m_height) {
                        data.push_back(&ColorPallet[0]);
                    }
                    i = info_header.ImageSize;
                    break;
                } case 2: { // Escape code for moving to new position on bitmap
                    unsigned int dx = pixel_data[i+2];
                    unsigned int dy = pixel_data[i+3];
                    for (int j = 0; j < dy*info_header.ImageWidth + dx; j++) {
                        data.push_back(&ColorPallet[0]);
                    }
                    i+=2;
                    break;
                } default: { // Escape code for a run of unique colors
                    unsigned int length = pixel_data[i+1];
                    unsigned int index;
                    for (int j = 0; j < length; j++) {
                        if (j%2 == 0) {
                            index = (pixel_data[i+2+(j/2)] >> 4);
                        } else {
                            index = (pixel_data[i+2+(j/2)] & 0b00001111);
                        }
                        data.push_back(&ColorPallet[index]);
                    }
                    i+=ceil(length/2.0);
                    i+=(i%2);
                    break;
                }
            }
        }
        i+=2;
    }
}

void image::BMPload8bppRLECompression(const unsigned char* pixel_data) {
    unsigned int i = 0;
    while (i < info_header.ImageSize) {
        unsigned int escape = pixel_data[i];
        if (escape != 0) { // if not an escape byte
            for (int j = 0; j < escape; j++) {
                data.push_back(&ColorPallet[pixel_data[i+1]]);
            }
        } else {
            switch (pixel_data[i+1]) {
                case 0: { // End of line
                    while (data.size() % info_header.ImageWidth != 0) {
                        data.push_back(&ColorPallet[0]);
                    }
                    break;
                } case 1: { // End of bitmap
                    while (data.size() < info_header.ImageWidth*info_header.ImageHeight) {
                        data.push_back(&ColorPallet[0]);
                    }
                    i = info_header.ImageSize;
                    break;
                } case 2: { // Jump to new position
                    unsigned int dx = pixel_data[i+2];
                    unsigned int dy = pixel_data[i+3];
                    for (int j = 0; j < dy*info_header.ImageWidth + dx; j++) {
                        data.push_back(&ColorPallet[0]);
                    }
                    i+=2;
                    break;
                } default: { // Series of n unique colors
                    unsigned int length = pixel_data[i+1];
                    for (int j = 0; j < length; j++) {
                        data.push_back(&ColorPallet[pixel_data[i+2+j]]);
                    }
                    i+=length;
                    i+=i%2; 
                    break;
                }
            }
        }
        i+=2;
    }
}
