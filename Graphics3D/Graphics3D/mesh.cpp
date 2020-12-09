//
//  mesh.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 12/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "mesh.hpp"

mesh::mesh() : triangles(std::vector<triangle>()) {
    
}

mesh::mesh(const std::vector<triangle>& tris) : triangles(tris) {
    
}

triangle mesh::operator[](const unsigned int& i) const {
    return triangles[i];
}

unsigned int mesh::size() const {
    return triangles.size();
}

void mesh::pop() {
    triangles.pop_back();
}

void mesh::erase(const unsigned int& start, const unsigned int& end = 0) {
    if (end == 0) {
        triangles.erase(triangles.begin() + start);
    } else {
        triangles.erase(triangles.begin() + start,
                        triangles.begin() + end);
    }
}

void mesh::push_back(const triangle &tri) {
    triangles.push_back(tri);
}

void mesh::insert(const unsigned int& i, const triangle& tri) {
    triangles.insert(triangles.begin() + i, tri);
}

std::string mesh::to_string() {
    std::string s = "";
    for (int i = 0; i < triangles.size(); i++) {
        s += "Triangle " + std::to_string(i) + ": " + triangles[i].to_string() + "\n";
    }
    return s;
}

void mesh::print() {
    std::cout << (*this).to_string() << std::endl;
}

mesh& mesh::operator+=(const vector3& v) {
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i] += v;
    }
    return *this;
}

mesh& mesh::operator-=(const vector3& v) {
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i] -= v;
    }
    return *this;
}

mesh& mesh::operator*=(const quaternion& q) {
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i] *= q;
    }
    return *this;
}

mesh mesh::operator+(const vector3& v) {
    mesh m(*this);
    for (int i = 0; i < m.triangles.size(); i++) {
        m.triangles[i] -= v;
    }
    return m;
}

mesh mesh::operator*(const quaternion& q) {
    mesh m(*this);
    for (int i = 0; i < m.triangles.size(); i++) {
        m.triangles[i] *= q;
    }
    return m;
}

mesh operator-(const mesh& tri, const vector3& v) {
    mesh m(tri);
    for (int i = 0; i < m.triangles.size(); i++) {
        m.triangles[i] -= v;
    }
    return m;
}
