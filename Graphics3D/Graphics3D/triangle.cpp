//
//  triangle.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "triangle.hpp"

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(cross_product(t_v2-t_v1, t_v3-t_v1)),
                    use_texture(false) {
}

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3,
                   const color& t_c) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(cross_product(t_v2-t_v1, t_v3-t_v1)),
                    tex(t_c),
                    use_texture(false) {
    
}

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3,
                   const vector3& t_normal) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(t_normal),
                    use_texture(false) {
    
}

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3,
                   const vector3& t_normal,
                   const color& t_c) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(t_normal),
                    tex(t_c),
                    use_texture(false) {
    
}

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3,
                   const texture& t_tex,
                   const vector2& t_tv1,
                   const vector2& t_tv2,
                   const vector2& t_tv3) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(cross_product(t_v2-t_v1, t_v3-t_v1)),
                    tex(t_tex),
                    tv1(t_tv1),
                    tv2(t_tv2),
                    tv3(t_tv3),
                    use_texture(true) {
    
}

triangle::triangle(const vector3& t_v1,
                   const vector3& t_v2,
                   const vector3& t_v3,
                   const vector3& t_normal,
                   const texture& t_tex,
                   const vector2& t_tv1,
                   const vector2& t_tv2,
                   const vector2& t_tv3) :
                    v1(t_v1),
                    v2(t_v2),
                    v3(t_v3),
                    normal(t_normal),
                    tex(t_tex),
                    tv1(t_tv1),
                    tv2(t_tv2),
                    tv3(t_tv3),
                    use_texture(true) {
    
}

vector3& triangle::operator[](const int& i) {
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
    throw std::out_of_range("Expected value between 0 and 3, got " + std::to_string(i));
}

triangle& triangle::operator+=(const vector3& v) {
    v1 += v;
    v2 += v;
    v3 += v;
    return *this;
}

triangle& triangle::operator-=(const vector3& v) {
    v1 -= v;
    v2 -= v;
    v3 -= v;
    return *this;
}

triangle& triangle::operator*=(const quaternion& q) {
    v1 *= q;
    v2 *= q;
    v3 *= q;
    return *this;
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
    float r = ((a*a + c*c - b*b) / (2*a*c)) * outer_radius();
    return (v1+v2)/2 + r * cross_product(v1-v2, v).normalized();
}

vector3 triangle::nine_point() const {
    return (orthocenter() + circumcenter()) / 2;
}

void triangle::rotate(const quaternion& q) {
    v1.rotate(q);
    v2.rotate(q);
    v3.rotate(q);
    normal.rotate(q);
}

triangle triangle::rotated(const quaternion& q) const {
    return triangle(v1.rotated(q),
                    v2.rotated(q),
                    v3.rotated(q),
                    normal.rotated(q));
}

void triangle::rotate(const vector3& axis,
                      const float& theta) {
    rotate(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

triangle triangle::rotated(const vector3& axis,
                           const float& theta) const {
    return rotated(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

void triangle::rotate(const vector3& axis,
                      const float& theta,
                      const vector3& origin) {
    v1.rotate(axis, theta, origin);
    v2.rotate(axis, theta, origin);
    v3.rotate(axis, theta, origin);
    normal.rotate(axis, theta, origin);
}

triangle triangle::rotated(const vector3& axis,
                           const float& theta,
                           const vector3& origin) const {
    return triangle(v1.rotated(axis, theta, origin),
                    v2.rotated(axis, theta, origin),
                    v3.rotated(axis, theta, origin),
                    normal.rotated(axis, theta, origin));
}

std::string triangle::to_string() const {
    return v1.to_string() + ", " + v2.to_string() + ", " + v3.to_string();
}

void triangle::print() const {
    std::cout << (*this).to_string() << std::endl;
}


triangle operator+(const vector3& v, const triangle& tri) {
    return triangle(tri.v1 + v, tri.v2 + v, tri.v3 + v);
}

triangle operator+(const triangle& tri, const vector3& v) {
    return triangle(tri.v1 + v, tri.v2 + v, tri.v3 + v);
}

triangle operator-(const triangle& tri, const vector3& v) {
    return triangle(tri.v1 - v, tri.v2 - v, tri.v3 - v);
}

triangle operator*(const triangle& tri, const quaternion& q) {
    return triangle(tri.v1 * q, tri.v2 * q, tri.v3 * q);
}

triangle operator*(const quaternion& q, const triangle& tri) {
    return triangle(tri.v1 * q, tri.v2 * q, tri.v3 * q);
    
}
