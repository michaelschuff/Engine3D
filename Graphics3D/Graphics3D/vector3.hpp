//
//  vector3.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 10/26/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef vector3_hpp
#define vector3_hpp

#include <stdio.h>
#include <iostream>

class quaternion;
class vector3 {
public:
    float x, y, z;
    vector3();
    vector3(const float&, const float&, const float&);
    
    void normalize();
    void projected_on(const vector3&);
    void rotate(const quaternion&);
    void rotate(const vector3&, const float&);
    void rotate(const vector3&, const float&, const vector3&);
    
    float magnitude() const;
    float square() const;
    float distance(const vector3&) const;
    vector3 crossed(const vector3&) const;
    vector3 normalized() const;
    vector3 rotated(const quaternion&) const;
    vector3 rotated(const vector3&, const float&) const;
    vector3 rotated(const vector3&, const float&, const vector3&) const;
    
    std::string to_string() const;
    void print() const;
    
    vector3& operator+=(const vector3&);
    vector3& operator-=(const vector3&);
    vector3& operator*=(const float&);
    vector3& operator*=(const quaternion&);
    vector3& operator/=(const float&);
    vector3& operator%=(const float&);
    vector3& operator%=(const vector3&);
    float& operator[](const int&);
};

vector3 operator+(const vector3&, const vector3&);
vector3 operator-(const vector3&, const vector3&);
vector3 operator-(const vector3&);
vector3 operator*(const float&, const vector3&);
vector3 operator*(const vector3&, const float&);
vector3 operator*(const vector3&, const quaternion&);
vector3 operator*(const quaternion&, const vector3&);
vector3 operator/(const vector3&, const float&);
vector3 operator%(const vector3&, const float&);
vector3 operator%(const vector3&, const vector3&);
float dot_product(const vector3&, const vector3&);
vector3 cross_product(const vector3&, const vector3&);
vector3 projection(const vector3&, const vector3&);

#endif /* vector3_hpp */
