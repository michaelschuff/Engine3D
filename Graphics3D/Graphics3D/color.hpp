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

template <typename T>
void color::set(const T& t_1, const T& t_2, const T& t_3, const T& t_a, COLOR_MODEL::COLOR_MODEL model) {
    switch (model) {
        case COLOR_MODEL::RGB16: {
            m_fa = t_a / 16.0;
            m_a = (uint8_t) m_fa;
            break;
        }
        case COLOR_MODEL::RGB32: {
            m_fa = t_a / 32.0;
            m_a = (uint8_t) m_fa;
            break;
        }
        case COLOR_MODEL::RGB256: {
            m_a = (uint8_t) t_a;
            m_fa = m_a / 255.0;
            break;
        } case COLOR_MODEL::fRGB: {
            m_fa = t_a;
            m_a = 255 * m_fa;
        } case COLOR_MODEL::HSV: {
            m_fa = t_a;
            m_a = 255 * m_fa;
            break;
        } case COLOR_MODEL::CMY: {
            m_a = t_a;
            m_fa = m_a / 255.0;
            break;
        }
    }
    set(t_1, t_2, t_3, model);
}

template <typename T>
void color::set(const T& t_1, const T& t_2, const T& t_3, COLOR_MODEL::COLOR_MODEL model) {
    switch (model) {
        case COLOR_MODEL::RGB16: {
            m_fr = t_1/16.0;
            m_fg = t_2/16.0;
            m_fb = t_3/16.0;
            
            set_RGB_from_fRGB();
            set_HSV_from_RGB();
            set_CYMK_from_RGB();
            break;
        } case COLOR_MODEL::RGB32: {
            m_fr = t_1/32.0;
            m_fg = t_2/32.0;
            m_fb = t_3/32.0;
            
            set_RGB_from_fRGB();
            set_HSV_from_RGB();
            set_CYMK_from_RGB();
            break;
        } case COLOR_MODEL::RGB256: {
            m_r = (uint8_t) t_1;
            m_g = (uint8_t) t_2;
            m_b = (uint8_t) t_3;
            
            set_fRGB_from_RGB();
            set_HSV_from_RGB();
            set_CYMK_from_RGB();
            break;
        } case COLOR_MODEL::fRGB: {
            m_fr = t_1;
            m_fg = t_2;
            m_fb = t_3;
            
            set_RGB_from_fRGB();
            set_HSV_from_RGB();
            set_CYMK_from_RGB();
            break;
        } case COLOR_MODEL::HSV: {
            m_h = t_1;
            m_s = t_2;
            m_v = t_3;
            
            set_RGB_from_HSV();
            set_fRGB_from_RGB();
            set_CYMK_from_RGB();
            break;
        } case COLOR_MODEL::CMY: {
            m_c = t_1;
            m_y = t_2;
            m_m = t_3;
            m_k = fmin(fmin(m_c, m_y), m_m);
            
            set_RGB_from_CYMK();
            set_fRGB_from_RGB();
            set_HSV_from_RGB();
            break;
        } default: {
            break;
        }
            
    }
}
#endif /* color_hpp */
