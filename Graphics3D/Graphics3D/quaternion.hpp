//
//  quaternion.h
//  Graphics3D
//
//  Created by Michael Schuff on 10/25/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef quaternion_hpp
#define quaternion_hpp

#include <stdio.h>
#include <math.h>
#include "vector3.hpp"

class quaternion {
public:
    float w, x, y, z;
    
    quaternion();
    quaternion(const float&,
               const float&,
               const float&,
               const float&);
    quaternion(const float&, const vector3&);
    quaternion(const vector3&);
    
    void normalize();
    
    float norm() const;
    float square() const;
    vector3 v() const;
    quaternion normalized() const;
    quaternion conjugate() const;
    quaternion inverse() const;
    quaternion reciprocal() const;
    
    quaternion &operator+=(const quaternion&);
    quaternion &operator-=(const quaternion&);
    quaternion &operator*=(const quaternion&);
    quaternion &operator*=(const float&);
    quaternion &operator/=(const float&);
    float& operator[](const int&);
    
    std::string to_string() const;
    void print() const;
};

quaternion operator+(const quaternion&, const quaternion&);
quaternion operator-(const quaternion&, const quaternion&);
quaternion operator*(const quaternion&, const float&);
quaternion operator*(const float&, const quaternion&);
quaternion operator*(const quaternion&, const quaternion&);
quaternion operator/(const quaternion&, const float&);
quaternion operator-(const quaternion&);

quaternion get_quaternion(const vector3&, const float&);
quaternion get_quaternion(const vector3&, const vector3&);
float distance(const quaternion&, const quaternion&);
quaternion operator*(const vector3&, const vector3&);

#endif /* quaternion_hpp */
