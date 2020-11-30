//
//  image.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/6/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <stdio.h>
#include <fstream>
#include <vector>
#include "color.hpp"


namespace ImageFileStructures {
    namespace BMP {
//        enum FileFormat {
//            BitmapArray = 0,    // 4142 'BA'
//            Bitmap = 1,         // 4D42 'BM'
//            ColorIcon = 2,      // 4943 'CI'
//            ColorPointer = 3,   // 5043 'CP'
//            Icon = 4,           // 4349 'IC'
//            Pointer = 5,        // 5450 'PT'
//        };
        
        #pragma pack(push)
        #pragma pack(1)
        struct FileHeader {
            // V1 - 14 bytes
            uint16_t FileType{ 0 };                 // 2 bytes
            uint32_t FileSize{ 0 };                 // 4 bytes
            uint16_t xHotSpot{ 0 };                 // 2 bytes
            uint16_t yHotSpot{ 0 };                 // 2 bytes
            uint32_t PixelDataOffset{ 0 };          // 4 bytes
        };
        
        struct BitmapCoreHeader {
            // V1 - 12 bytes
            uint32_t HeaderSize{ 0 };               // 4 bytes
            int16_t ImageWidth{ 0 };                // 2 bytes
            int16_t ImageHeight{ 0 };               // 2 bytes
            uint16_t Planes{ 0 };                   // 2 bytes
            uint16_t BitsPerPixel{ 0 };             // 2 bytes
            
            // V2 - 64 bytes
            uint32_t  Compression{ 0 };             // 4 bytes
            uint32_t  ImageSize{ 0 };               // 4 bytes
            int32_t  XResolution{ 0 };              // 4 bytes
            int32_t  YResolution{ 0 };              // 4 bytes
            uint32_t  TotalColors{ 0 };             // 4 bytes
            uint32_t  ImportantColors{ 0 };         // 4 bytes
            uint16_t  Units{ 0 };                   // 2 bytes
            uint16_t  Reserved{ 0 };                // 2 bytes
            uint16_t  Recording{ 0 };               // 2 bytes
            uint16_t  Rendering{ 0 };               // 2 bytes
            uint32_t  Size1{ 0 };                   // 4 bytes
            uint32_t  Size2{ 0 };                   // 4 bytes
            uint32_t  ColorEncoding{ 0 };           // 4 bytes
            uint32_t  Identifier{ 0 };              // 4 bytes
        };
        
        struct ColorEndPoint {
            unsigned int RedEndPointInt : 2;        // 2 bit int part
            unsigned int RedEndPointFrac : 30;      // 30 bit fractional
            
            unsigned int GreenEndPointInt : 2;      // 2 bit int part
            unsigned int GreenEndPointFrac : 30;    // 30 bit fractional
            
            unsigned int BlueEndPointInt : 2;       // 2 bit int part
            unsigned int BlueEndPointFrac : 30;     // 30 bit fractional
        };
        
        struct BitmapInfoHeader {
            // V1 - 40 bytes
            uint32_t HeaderSize{ 0 };               // 4 bytes
            int32_t ImageWidth{ 0 };                // 4 bytes
            int32_t ImageHeight{ 0 };               // 4 bytes
            uint16_t Planes{ 0 };                   // 2 bytes
            uint16_t BitsPerPixel{ 0 };             // 2 bytes
            uint32_t Compression{ 0 };              // 4 bytes
            uint32_t ImageSize{ 0 };                // 4 bytes
            int32_t XpixelsPerMeter{ 0 };           // 4 bytes
            int32_t YpixelsPerMeter{ 0 };           // 4 bytes
            uint32_t TotalColors{ 0 };              // 4 bytes
            uint32_t ImportantColors{ 0 };          // 4 bytes
            
            // V2 - 52 bytes
            uint32_t RedBitmask{ 0 };               // 4 bytes
            uint32_t GreenBitmask{ 0 };             // 4 bytes
            uint32_t BlueBitmask{ 0 };              // 4 bytes
            
            // V3 - 56 bytes
            uint32_t AlphaBitmask{ 0 };             // 4 bytes
            
            // V4 - 108 bytes
            uint32_t ColorSpaceType{ 0 };           // 4 bytes
            ColorEndPoint ColorEndpoints[3];        // 36 bytes
            uint32_t RedGamma{ 0 };                 // 4 bytes
            uint32_t GreenGamma{ 0 };               // 4 bytes
            uint32_t BlueGamma{ 0 };                // 4 bytes
            
            // V5 - 124 bytes
            uint32_t Intent{ 0 };                   // 4 bytes
            uint32_t ProfileData{ 0 };              // 4 bytes
            uint32_t ProfileSize{ 0 };              // 4 bytes
            uint32_t Reserved{ 0 };                 // 4 bytes
        };
        
        struct BitmapColorHeader {
            uint32_t RedBitmask{ 0x00ff0000 };      // 4 bytes
            uint32_t GreenBitmask{ 0x0000ff00 };    // 4 bytes
            uint32_t BlueBitmask{ 0x000000ff };     // 4 bytes
            uint32_t AlphaBitmask{ 0xff000000 };    // 4 bytes
            uint32_t ColorSpaceType{ 0x73524742 };  // 4 bytes
        };
        
        struct Color {
            // V1 - 3 bytes
            uint8_t Blue{ 0 };                      // 4 bytes
            uint8_t Green{ 0 };                     // 4 bytes
            uint8_t Red{ 0 };                       // 4 bytes
            
            // V2 - 4 bytes
            uint8_t Reserved{ 0 };                  // 4 bytes
        };
        #pragma pack(pop)
    }
}

class image {
private:
    unsigned int m_width, m_height;
    std::vector<color*> data;
    std::vector<color> ColorPallet;
    
    bool isTopDown = false;
    
//    ImageFileStructures::BMP::FileFormat file_format;
    
    ImageFileStructures::BMP::FileHeader file_header;
    ImageFileStructures::BMP::BitmapCoreHeader core_header;
    ImageFileStructures::BMP::BitmapInfoHeader info_header;
    ImageFileStructures::BMP::BitmapColorHeader color_header;
    
    void loadBMPFile(const std::string&);
    void BMPload1bpp(const unsigned char*);
    void BMPload4bpp(const unsigned char*);
    void BMPload8bpp(const unsigned char*);
    void BMPload16bpp(const unsigned char*);
    void BMPload24bpp(const unsigned char*);
    void BMPload32bpp(const unsigned char*);
    void BMPload4bppRLECompression(const unsigned char*);
    void BMPload8bppRLECompression(const unsigned char*);
    
public:
    image();
    image(const color&);
    image(const color&, const unsigned int&, const unsigned int&);
    image(const std::string&);
    
    unsigned int width();
    unsigned int height();
    color* get(const unsigned int&, const unsigned int&);
    
    void loadImage(const std::string&);
};

#endif /* image_hpp */
