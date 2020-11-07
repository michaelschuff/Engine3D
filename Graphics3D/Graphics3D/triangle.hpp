//
//  triangle.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

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
    texture *tex;
    color c;
    
    bool use_texture;
    
    triangle(const vector3 &t_v1, const vector3 &t_v2, const vector3 &t_v3, const vector3 &t_normal=cross_product(t_v2-t_v1, t_v3-t_v1), const color &t_c=color()) : v1(t_v1), v2(t_v2), v3(t_v3), normal(t_normal), c(t_c), use_texture(false) {}
    triangle(const vector3 &t_v1, const vector3 &t_v2, const vector3 &t_v3, const color &t_c=color()) : v1(t_v1), v2(t_v2), v3(t_v3), normal(cross_product(t_v2-t_v1, t_v3-t_v1)), c(t_c), use_texture(false) {}
    triangle(const vector3 &t_v1, const vector3 &t_v2, const vector3 &t_v3, const vector3 &t_normal, const texture &t_tex, const vector2 &t_tv1, const vector2 &t_tv2, const vector2 &t_tv3) : v1(t_v1), v2(t_v2), v3(t_v3), normal(t_normal), tex(*t_tex), tv1(t_tv1), tv2(t_tv2), tv3(t_tv3), use_texture(true) {}
    triangle(const vector3 &t_v1, const vector3 &t_v2, const vector3 &t_v3, const texture &t_tex, const vector2 &t_tv1, const vector2 &t_tv2, const vector2 &t_tv3) : v1(t_v1), v2(t_v2), v3(t_v3), normal(cross_product(t_v2-t_v1, t_v3-t_v1)), tex(*t_tex), tv1(t_tv1), tv2(t_tv2), tv3(t_tv3), use_texture(true) {}
    triangle(const triangle &tri) : v1(tri.v1), v2(tri.v2), v3(tri.v3), normal(tri.normal), tex(tri.tex), c(tri.c), use_texture(tri.use_texture) {}
    
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
    vector3 rotated(const quaternion&) const;
    vector3 rotated(const vector3&, const float&) const;
    vector3 rotated(const vector3&, const float&, const vector3&) const;
    
    std::string to_string() const;
    void print() const;
    
    triangle &operator=(const triangle &tri);
    vector3 &operator[](const int&);
};

triangle &triangle::operator=(const triangle &tri) {
    v1 = tri.v1;
    v2 = tri.v2;
    v3 = tri.v3;
    normal = tri.normal;
    tex = tri.tex;
    tv1 = tri.tv1;
    tv2 = tri.tv2;
    tv3 = tri.tv3;
    c = tri.c;
    use_texture = tri.use_texture;
    return *this;
}

vector3 &triangle::operator[](const int &i) {
    if (i >= 0 && i < 3) {
        switch (i % 3) {
            case 0:
                return v1;
            case 1:
                return v2;
            case 2:
                return v3;
        }
    }
    return vector3();
}

float triangle::A() const {
    return (v3 - v2).magnitude();
}

float triangle::B() const {
    return (v1 - v3).magnitude();
}

float triangle::C() const {
    return (v2 - v1).magnitude();
}

float triangle::area() const {
    return 0.5 * cross_product(v2-v1, v3-v1).magnitude();
}

float triangle::outer_radius() const {
    return A()*B()*C() / (4*area());
}

vector3 triangle::incenter() const {
    float a = A(), b = B(), c = C();
    return (a*v1 + b*v2 + c*v3) / (a+b+c);
}

vector3 triangle::centroid() const {
    return (v1+v2+v3) / 3;
}

vector3 triangle::orthocenter() const {
    return (v1+v2+v3) - 2*circumcenter();
}

vector3 triangle::circumcenter() const {
    vector3 v(cross_product(v3-v2, v1-v2));
    float a = A(), b = B(), c = C();
    float r = ((a*a + c*c - b*b) / (2*a*c)) * outer_radius(a, b, c);
    return (v1+v2)/2 + r * cross_product(v1-v2, v).normalized();
}

vector3 triangle::nine_point() const {
    return (orthocenter() + circumcenter()) / 2;
}

void triangle::rotate(const quaternion &q) {
    v1.rotate(q);
    v2.rotate(q);
    v3.rotate(q);
    normal.rotate(q);
}

vector3 triangle::rotated(const quaternion &q) const {
    return triangle(v1.rotated(q), v2.rotated(q), v3.rotated(q), normal.rotated(q));
}

void triangle::rotate(const vector3 &axis, const float &theta) {
    rotate(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

vector3 triangle::rotated(const vector3 &axis, const float &theta) const {
    return rotated(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

void triangle::rotate(const vector3 &axis, const float &theta, const vector3 &origin) {
    v1.rotate(axis, theta, origin);
    v2.rotate(axis, theta, origin);
    v3.rotate(axis, theta, origin);
    normal.rotate(axis, theta, origin);
}

vector3 triangle::rotated(const vector3 &axis, const float &theta, const vector3 &origin) const {
    return triangle(v1.rotated(axis, theta, origin), v2.rotated(axis, theta, origin), v3.rotated(axis, theta, origin), normal.rotated(axis, theta, origin));
}

std::string triangle::to_string() const {
    return v1.to_string() + ", " + v2.to_string() + ", " + v3.to_string();
}

void triangle::print() const {
    std::cout << (*this).to_string() << std::endl;
}

#endif /* triangle_hpp */
