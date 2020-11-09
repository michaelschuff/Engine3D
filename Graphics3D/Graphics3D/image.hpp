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
        #pragma pack(push)
        #pragma pack(1)
        struct FileHeader { // 14 bytes
            uint16_t FileType{ 0 };         // 2 bytes
            uint32_t FileSize{ 0 };         // 4 bytes
            uint16_t Reserved1{ 0 };        // 2 bytes
            uint16_t Reserved2{ 0 };        // 2 bytes
            uint32_t PixelDataOffset{ 0 };  // 4 bytes
        };
        struct InfoHeader { // 40 bytes
            uint32_t HeaderSize{ 0 };       // 4 bytes
            int32_t ImageWidth{ 0 };        // 4 bytes
            int32_t ImageHeight{ 0 };       // 4 bytes
            uint16_t Planes{ 0 };           // 2 bytes
            uint16_t BitsPerPixel{ 0 };     // 2 bytes
            uint32_t Compression{ 0 };      // 4 bytes
            uint32_t ImageSize{ 0 };        // 4 bytes
            int32_t XpixelsPerMeter{ 0 };   // 4 bytes
            int32_t YpixelsPerMeter{ 0 };   // 4 bytes
            uint32_t TotalColors{ 0 };      // 4 bytes
            uint32_t ImportantColors{ 0 };  // 4 bytes
        };
        struct ColorHeader { // optional 84 bytes
            uint32_t RedBitMask{ 0x00ff0000 };      // Bit mask for the red channel
            uint32_t GreenBitMask{ 0x0000ff00 };    // Bit mask for the green channel
            uint32_t BlueBitMask{ 0x000000ff };     // Bit mask for the blue channel
            uint32_t AlphaBitMask{ 0xff000000 };    // Bit mask for the alpha channel
            uint32_t ColorSpaceType{ 0x73524742 };  // Default "sRGB" (0x73524742)
            unsigned char* ColorPallet;
        };
        #pragma pack(pop)
    }
}

class image {
private:
    unsigned int m_width, m_height;
    void loadBMPFile(const std::string&);
    std::vector<color*> data;
    ImageFileStructures::BMP::FileHeader bfh;
    ImageFileStructures::BMP::InfoHeader bih;
    ImageFileStructures::BMP::ColorHeader bch;
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
