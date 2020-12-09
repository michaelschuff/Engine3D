//
//  mesh.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 12/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <vector>
#include <iterator>

#include "triangle.hpp"

class mesh {
public:
    std::vector<triangle> triangles;
    
    mesh();
    mesh(const std::vector<triangle>& tris);
    
    triangle operator[](const unsigned int& i) const;
    
    unsigned int size() const;
    void pop();
    void erase(const unsigned int& start, const unsigned int& end);
    void push_back(const triangle& tri);
    void insert(const unsigned int& i, const triangle& tri);
    
    std::string to_string();
    void print();
    
    mesh& operator+=(const vector3&);
    mesh& operator-=(const vector3&);
    mesh& operator*=(const quaternion&);
    mesh operator*(const quaternion& q);
    mesh operator+(const vector3& v);
};

mesh operator-(const mesh& tri, const vector3& v);

#endif /* mesh_hpp */
