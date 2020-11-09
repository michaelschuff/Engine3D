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
    
    quaternion(const float &t_w, const float &t_x, const float &t_y, const float &t_z) : w(t_w), x(t_x), y(t_y), z(t_z) {}
    quaternion(const float &k, const vector3 &v) : w(k), x(v.x), y(v.y), z(v.z) {}
    quaternion(const vector3 &v) : w(0), x(v.x), y(v.y), z(v.z) {}
    
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

#endif /* quaternion_hpp */
