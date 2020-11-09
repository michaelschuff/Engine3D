//
//  color.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef color_hpp
#define color_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

namespace COLOR_MODEL {
    enum COLOR_MODEL {
        RGB16 = 1,
        RGB32 = 2,
        RGB256 = 3,
        fRGB = 4,
        HSV = 5,
        CMY = 6
    };
}

class color {
private:
    uint16_t m_r, m_g, m_b;
    uint16_t m_c, m_y, m_m, m_k;
    uint16_t m_a;
    
    float m_h, m_s, m_v;
    float m_fr, m_fg, m_fb;
    float m_fa;
    
    void set_HSV_from_RGB();
    void set_CYMK_from_RGB();
    void set_fRGB_from_RGB();
    void set_RGB_from_HSV();
    void set_RGB_from_CYMK();
    void set_RGB_from_fRGB();
public:
    template <typename T>
    void set(const T&, const T&, const T&, COLOR_MODEL::COLOR_MODEL);
    template <typename T>
    void set(const T&, const T&, const T&, const T&, COLOR_MODEL::COLOR_MODEL);
    
    uint16_t r() const;
    uint16_t g() const;
    uint16_t b() const;
    uint16_t a() const;
    uint16_t c() const;
    uint16_t m() const;
    uint16_t y() const;
    uint16_t k() const;
    float fr() const;
    float fg() const;
    float fb() const;
    float fa() const;
    float h() const;
    float s() const;
    float v() const;
    
    color();
    color(const unsigned char&, const unsigned char&, const unsigned char&);
    color(const unsigned char&, const unsigned char&, const unsigned char&, const unsigned char&);
    color(const unsigned char&, const unsigned char&, const unsigned char&, COLOR_MODEL::COLOR_MODEL);
    color(const unsigned char&, const unsigned char&, const unsigned char&, const unsigned char&, COLOR_MODEL::COLOR_MODEL);
    template <typename T>
    color(const T&, const T&, const T&);
    template <typename T>
    color(const T&, const T&, const T&, const T&);
    template <typename T>
    color(const T&, const T&, const T&, COLOR_MODEL::COLOR_MODEL);
    template <typename T>
    color(const T&, const T&, const T&, const T&, COLOR_MODEL::COLOR_MODEL);
    
    std::string to_string() const;
    void print() const;
    
    color& operator+=(const color&);
    color& operator-=(const color&);
    color& operator*=(const float&);
    color& operator/=(const float&);
};

template <typename T>
color::color(const T& t_1,
             const T& t_2,
             const T& t_3) :
             m_a(255),
             m_fa(1.0) {
    set(t_1, t_2, t_3, COLOR_MODEL::RGB256);
}

template <typename T>
color::color(const T& t_1,
             const T& t_2,
             const T& t_3,
             COLOR_MODEL::COLOR_MODEL model) :
             m_a(255),
             m_fa(1.0) {
    set(t_1, t_2, t_3, model);
}
 
template <typename T>
color::color(const T& t_1,
             const T& t_2,
             const T& t_3,
             const T& t_a) {
    set(t_1, t_2, t_3, t_a, COLOR_MODEL::RGB256);
}

template <typename T>
color::color(const T& t_1,
             const T& t_2,
             const T& t_3,
             const T& t_a,
             COLOR_MODEL::COLOR_MODEL model) {
    set(t_1, t_2, t_3, t_a, model);
}
#endif /* color_hpp */
