//
//  texture.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include "image.hpp"
#include "color.hpp"

class texture {
private:
    enum ImageType {
        BMP
    };
    ImageType image_type;
    image img;
public:
    texture();
    texture(const color&);
    texture(const color&, const unsigned int&, const unsigned int&);
    texture(const std::string&);
    
    void ReadBMP(const std::string&);
    
    
    color* operator()(const unsigned int&, const unsigned int&);
};

#endif /* texture_hpp */
