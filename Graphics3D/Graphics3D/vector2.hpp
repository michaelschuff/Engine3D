//
//  vector2.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef vector2_hpp
#define vector2_hpp

#include <stdio.h>
#include <iostream>

class vector2 {
public:
    float x, y;
    
    vector2();
    vector2(const float&, const float&);
    
    void normalize();
    void projected_on(const vector2&);
    void rotate(const float&);
    void rotate(const vector2&, const float&);
    
    float magnitude() const;
    float square() const;
    float distance(const vector2&) const;
    vector2 normalized() const;
    vector2 rotated(const float&) const;
    vector2 rotated(const vector2&, const float&) const;
    
    std::string to_string() const;
    void print() const;
    
    vector2 &operator+=(const vector2&);
    vector2 &operator-=(const vector2&);
    vector2 &operator*=(const float&);
    vector2 &operator/=(const float&);
    vector2 &operator%=(const float&);
    vector2 &operator%=(const vector2&);
    float& operator[](const int&);
};

vector2 operator+(const vector2&, const vector2&);
vector2 operator-(const vector2&, const vector2&);
vector2 operator-(const vector2&);
vector2 operator*(const float&, const vector2&);
vector2 operator*(const vector2&, const float&);
vector2 operator/(const vector2&, const float&);
vector2 operator%(const vector2&, const float&);
vector2 operator%(const vector2&, const vector2&);
float dot_product(const vector2&, const vector2&);
vector2 projection(const vector2&, const vector2&);

#endif /* vector2_hpp */
