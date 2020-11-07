//
//  texture.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <vector>
#include <fstream>
#include "image.hpp"

class texture {
private:
    enum ImageType {
        BMP
    }
    ImageType image_type;
    image img;
public:
    texture(const string&);
    texture(const texture &t) : data(t.data), width(t.width), height(t.height) {}
    
    void ReadBMP(const string&);
    
    
//    color &operator()(const int&, const int&);
};

texture::texture(const string &file_path) {
    switch(file_path.substr(file_path.size() - 4)) {
        case ".bmp": {
            bmp_img = BMPimage(file_path);
        }
    }
}

color &texture::operator()(const int &x, const int &y) {
    switch (
    return data[y * width + x];
}

#endif /* texture_hpp */
