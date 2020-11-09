//
//  triangle.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "vector2.hpp"
#include "vector3.hpp"
#include "quaternion.hpp"
#include "texture.hpp"
#include "color.hpp"

class triangle {
public:
    vector3 v1, v2, v3, normal;
    vector2 tv1, tv2, tv3;
    texture tex;
    
    bool use_texture;
    
    triangle(const vector3&, const vector3&, const vector3&);
    triangle(const vector3&, const vector3&, const vector3&, const color&);
    triangle(const vector3&, const vector3&, const vector3&, const vector3&);
    triangle(const vector3&, const vector3&, const vector3&, const vector3&, const color&);
    triangle(const vector3&, const vector3&, const vector3&, const texture&, const vector2&, const vector2&, const vector2&);
    triangle(const vector3&, const vector3&, const vector3&, const vector3&, const texture&, const vector2&, const vector2&, const vector2&);
    
    void rotate(const quaternion&);
    void rotate(const vector3&, const float&);
    void rotate(const vector3&, const float&, const vector3&);
    
    float A() const;
    float B() const;
    float C() const;
    float area() const;
    float outer_radius() const;
    vector3 incenter() const;
    vector3 centroid() const;
    vector3 orthocenter() const;
    vector3 circumcenter() const;
    vector3 nine_point() const;
    triangle rotated(const quaternion&) const;
    triangle rotated(const vector3&, const float&) const;
    triangle rotated(const vector3&, const float&, const vector3&) const;
    
    std::string to_string() const;
    void print() const;
    
    vector3& operator[](const int&);
};

#endif /* triangle_hpp */
