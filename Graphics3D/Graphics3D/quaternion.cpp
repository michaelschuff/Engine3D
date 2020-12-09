//
//  quaternion.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/8/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "quaternion.hpp"

quaternion::quaternion() : w(1), x(0), y(0), z(0) {
    
}

quaternion::quaternion(const float &t_w,
                       const float &t_x,
                       const float &t_y,
                       const float &t_z) : w(t_w), x(t_x), y(t_y), z(t_z) {
    
}

quaternion::quaternion(const float &k,
                       const vector3 &v) : w(k), x(v.x), y(v.y), z(v.z) {
    
}

quaternion::quaternion(const vector3 &v) : w(0), x(v.x), y(v.y), z(v.z) {
    
}

quaternion operator+(const quaternion& q1,
                     const quaternion& q2) {
    return quaternion(q1.w+q2.w, q1.x+q2.x, q1.y+q2.y, q1.z+q2.z);
}

quaternion operator-(const quaternion& q1,
                     const quaternion& q2) {
    return quaternion(q1.w-q2.w, q1.x-q2.x, q1.y-q2.y, q1.z-q2.z);
}

quaternion operator*(const quaternion& q,
                     const float& k) {
    return quaternion(k*q.w, k*q.x, k*q.y, k*q.z);
}

quaternion operator*(const float& k,
                     const quaternion& q) {
    return quaternion(k*q.w, k*q.x, k*q.y, k*q.z);
}

quaternion operator*(const quaternion& q1,
                     const quaternion& q2) {
    return quaternion(q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
                      q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
                      q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
                      q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w);
}

quaternion operator/(const quaternion& q,
                     const float& k) {
    if (k == 0) {
        return q;
    }
    return quaternion(q.w/k, q.x/k, q.y/k, q.z/k);
}

quaternion& quaternion::operator+=(const quaternion& q) {
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
    return *this;
}

quaternion& quaternion::operator-=(const quaternion& q) {
    w -= q.w;
    x -= q.x;
    y -= q.y;
    z -= q.z;
    return *this;
}

quaternion& quaternion::operator*=(const float& k) {
    w *= k;
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

quaternion& quaternion::operator*=(const quaternion& q) {
    quaternion q1(*this * q);
    w = q1.w;
    x = q1.x;
    y = q1.y;
    z = q1.z;
    return *this;
}

quaternion& quaternion::operator/=(const float& k) {
    if (k != 0) {
        w /= k;
        x /= k;
        y /= k;
        z /= k;
    }
    return *this;
}

float& quaternion::operator[](const int& i) {
    if (i >= 0 && i < 4) {
        switch (i % 4) {
            case 0:
                return w;
            case 1:
                return x;
            case 2:
                return y;
            case 3:
                return z;
        }
    }
    throw std::out_of_range("Expected value between 0 and 4, got " + std::to_string(i));
}

quaternion operator-(const quaternion& q) {
    return quaternion(-q.w, -q.x, -q.y, -q.z);
}

float quaternion::norm() const {
    return sqrt(w*w + x*x + y*y + z*z);
}

float quaternion::square() const {
    return w*w + x*x + y*y + z*z;
}

vector3 quaternion::v() const {
    return vector3(x, y, z);
}

quaternion quaternion::normalized() const {
    return (*this) / norm();
}

quaternion quaternion::conjugate() const {
    return quaternion(w, -x, -y, -z);
}

quaternion quaternion::inverse() const {
    return conjugate() / (w*w + x*x + y*y + z*z);
}

quaternion quaternion::reciprocal() const {
    return conjugate() / square();
}

void quaternion::normalize() {
    (*this) /= norm();
}

quaternion get_quaternion(const vector3& v1,
                          const vector3& v2) {
    return quaternion(v1.magnitude() * v2.magnitude() + dot_product(v1, v2), cross_product(v1, v2)).normalized();
}

quaternion get_quaternion(const vector3& axis,
                          const float& theta) {
    return quaternion(cos(theta/2), sin(theta/2) * axis.normalized()).normalized();
}

float distance(const quaternion& q1,
               const quaternion& q2) {
    return (q1-q2).norm();
}

quaternion operator*(const vector3& v1,
                     const vector3& v2) {
    return quaternion(-dot_product(v1, v2), cross_product(v1, v2));
}


static std::string remove_terminating_zeros(std::string str) {
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    return str;
}

std::string quaternion::to_string() const {
    return ("<" + remove_terminating_zeros(std::to_string(w)) + ", " + remove_terminating_zeros(std::to_string(x)) + ", " + remove_terminating_zeros(std::to_string(y)) + ", " + remove_terminating_zeros(std::to_string(z)) + ">");
}

void quaternion::print() const {
    std::cout << (*this).to_string() << std::endl;
}


void vector3::rotate(const quaternion& q) {
    quaternion q1 = q * quaternion(*this) * q.conjugate();
    x = q1.x;
    y = q1.y;
    z = q1.z;
}

vector3 vector3::rotated(const quaternion& q) const {
    return (q * quaternion(0, *this) * q.conjugate()).v();
}

void vector3::rotate(const vector3& axis,
                     const float& theta) {
    rotate(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

vector3 vector3::rotated(const vector3& axis,
                         const float& theta) const {
    return rotated(quaternion(cos(theta/2), axis.normalized() * sin(theta)/2));
}

void vector3::rotate(const vector3& axis,
                     const float& theta,
                     const vector3& origin) {
    vector3 v1 = (*this - origin).rotated(axis, theta);
    x = v1.x + origin.x;
    y = v1.y + origin.y;
    z = v1.z + origin.z;
}

vector3 vector3::rotated(const vector3& axis,
                         const float& theta,
                         const vector3& origin) const {
    return origin + (*this - origin).rotated(axis, theta);
}
