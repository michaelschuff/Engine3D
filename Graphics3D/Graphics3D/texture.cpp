//
//  texture.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "texture.hpp"

texture::texture() {
    
}

texture::texture(const color& t_c) : img(t_c) {
    
}

texture::texture(const color& t_c,
                 const unsigned int& t_width,
                 const unsigned int& t_height) :
                 img(t_c, t_width, t_height) {
    
}

texture::texture(const std::string& file_path) : img(file_path) {
    
}

color* texture::operator()(const unsigned int& x, const unsigned int& y) {
    return img.get(x, y);
}
