//
//  color.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/2/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef color_hpp
#define color_hpp

#include <iostream>
#include <cmath>

namespace COLOR_MODEL {
enum COLOR_MODEL {
    RGB = 1,
    fRGB = 2,
    HSV = 3,
    CMY = 4
};
}

class color {
private:
    unsigned char m_r, m_g, m_b;
    unsigned char m_c, m_y, m_m, m_k;
    unsigned char m_a;
    
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
    unsigned char r() const;
    unsigned char g() const;
    unsigned char b() const;
    unsigned char a() const;
    unsigned char c() const;
    unsigned char m() const;
    unsigned char y() const;
    unsigned char k() const;
    float fr() const;
    float fg() const;
    float fb() const;
    float fa() const;
    float h() const;
    float s() const;
    float v() const;
    
    template <typename T>
    color(const T& t_1, const T& t_2, const T& t_3, COLOR_MODEL::COLOR_MODEL model) : m_a(255), m_fa(1.0) {
        set(t_1, t_2, t_3, model);
    }
    template <typename T>
    color(const T& t_1, const T& t_2, const T& t_3, const T& t_a = 255, COLOR_MODEL::COLOR_MODEL model = COLOR_MODEL::RGB) {
        set(t_1, t_2, t_3, t_a, model);
    }
    
    std::string to_string() const;
    void print() const;
    
    color& operator+=(const color&);
    color& operator-=(const color&);
    color& operator*=(const float&);
    color& operator/=(const float&);
};

color& color::operator+=(const color& c) {
    unsigned char t_r = (m_r+c.r())/2;
    unsigned char t_g = (m_g+c.g())/2;
    unsigned char t_b = (m_g+c.b())/2;
    m_a = (m_a+c.a())/2;
    set(t_r, t_g, t_b, COLOR_MODEL::RGB);
    return *this;
}

color& color::operator-=(const color& c) {
    unsigned char t_c = (m_c+c.c())/2;
    unsigned char t_m = (m_m+c.m())/2;
    unsigned char t_y = (m_y+c.y())/2;
    m_a = (m_a+c.a())/2;
    set(t_c, t_m, t_y, COLOR_MODEL::CMY);
    return *this;
}

color& color::operator*=(const float& f) {
    if (f > 0) {
        if (f < 1) {
            set(f*m_r, f*m_g, f*m_b, COLOR_MODEL::RGB);
        }
        set(m_c/f, m_m/f, m_y/f, COLOR_MODEL::CMY);
    } else if (f == 0) {
        set(0, 0, 0, COLOR_MODEL::RGB);
    } else {
        std::cout << "Cannot multiply color by negative" << std::endl;
    }
    return *this;
}

color& color::operator/=(const float& f) {
    if (f > 0) {
        if (f < 1) {
            set(f*m_c, f*m_m, f*m_y, COLOR_MODEL::CMY);
        }
        set(m_r/f, m_g/f, m_b/f, COLOR_MODEL::RGB);
    } else if (f == 0) {
        std::cout << "Cannot divide by 0" << std::endl;
    } else {
        std::cout << "Cannot divide color by negative" << std::endl;
    }
    return *this;
}


color operator+(const color& c1, const color& c2) {
    unsigned char r = (c1.r() + c2.r())/2;
    unsigned char g = (c1.g() + c2.g())/2;
    unsigned char b = (c1.b() + c2.b())/2;
    unsigned char a = (c1.a() + c2.a())/2;
    return color(r, g, b, a, COLOR_MODEL::RGB);
}

color operator-(const color& c1, const color& c2) {
    unsigned char c = (c1.c() + c2.c())/2;
    unsigned char m = (c1.m() + c2.m())/2;
    unsigned char y = (c1.y() + c2.y())/2;
    unsigned char a = (c1.a() + c2.a())/2;
    return color(c, m, y, a, COLOR_MODEL::CMY);
}

float square(const color&c1, const color& c2) {
    return pow(c1.r()-c2.r(), 2) + pow(c1.g()-c2.g(), 2) + pow(c1.b()-c2.b(), 2);
}

float distance(const color& c1, const color& c2) {
    return sqrt(square(c1, c2));
}

float red_mean(const color& c1, const color& c2) {
    float r = (c1.r()+c2.r()) / 2.0;
    float rP = pow(c1.r()-c2.r(), 2);
    float gP = pow(c1.g()-c2.g(), 2);
    float bP = pow(c1.b()-c2.b(), 2);
    return sqrt((2+r/256)*rP + 4*gP + (2+(255-r)/256)*bP);
}

bool operator==(const color& c1, const color& c2) {
    return c1.r()==c2.r() && c1.g()==c2.g() && c1.b()==c2.b();
}

bool operator!=(const color& c1, const color& c2) {
    return c1.r()!=c2.r() || c1.g()!=c2.g() || c1.b()!=c2.b();
}

unsigned char color::r() const { return m_r; }
unsigned char color::g() const { return m_g; }
unsigned char color::b() const { return m_b; }
unsigned char color::a() const { return m_a; }
unsigned char color::c() const { return m_c; }
unsigned char color::m() const { return m_m; }
unsigned char color::y() const { return m_y; }
unsigned char color::k() const { return m_k; }
float color::fr() const { return m_fr; }
float color::fg() const { return m_fb; }
float color::fb() const { return m_fg; }
float color::fa() const { return m_fa; }
float color::h() const { return m_h; }
float color::s() const { return m_s; }
float color::v() const { return m_v; }

template <typename T>
void color::set(const T& t_1, const T& t_2, const T& t_3, const T& t_a, COLOR_MODEL::COLOR_MODEL model) {
    switch (model) {
        case COLOR_MODEL::RGB: {
            m_a = t_a;
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
        case COLOR_MODEL::RGB: {
            m_r = t_1;
            m_g = t_2;
            m_b = t_3;
            
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

void color::set_HSV_from_RGB() {
    unsigned char max_chroma = fmax(fmax(m_r, m_g), m_b);
    unsigned char min_chroma = fmin(fmin(m_r, m_g), m_b);
    unsigned char delta_chroma = max_chroma - min_chroma;
      
    if (delta_chroma == 0) {
        m_h = 0;
        m_s = 0;
        m_v = max_chroma;
    } else {
        if (max_chroma == m_r) {
            m_h = 60 * (fmod(((m_g - m_b) / delta_chroma), 6));
        } else if (max_chroma == m_g) {
            m_h = 60 * (((m_b - m_r) / delta_chroma) + 2);
        } else if (max_chroma == m_b) {
            m_h = 60 * (((m_r - m_g) / delta_chroma) + 4);
        } else {
            m_h = 0;
        }
        
        if (max_chroma == 0) {
            m_s = 0;
        } else {
            m_s = (float) delta_chroma / max_chroma;
        }
        
        m_v = max_chroma;
    }

    if (m_h < 0) {
        m_h += 360;
    }
}

void color::set_CYMK_from_RGB() {
    float t_c = 255 - m_r;
    float t_m = 255 - m_g;
    float t_y = 255 - m_b;
    m_k = fmin(fmin(t_c, t_m), t_y);
    
    m_c = (t_c - m_k) / (1 - m_k/255.0);
    m_m = (t_m - m_k) / (1 - m_k/255.0);
    m_y = (t_y - m_k) / (1 - m_k/255.0);
}

void color::set_fRGB_from_RGB() {
    m_fr = m_r / 255.0;
    m_fg = m_g / 255.0;
    m_fb = m_b / 255.0;
}

void color::set_RGB_from_HSV() {
    float chroma = m_v * m_s;
    float hue_prime = fmod(m_h / 60, 6);
    float X = chroma * (1 - fabs(fmod(hue_prime, 2) - 1));

    if (0 <= hue_prime && hue_prime < 1) {
        m_r = m_v;
        m_g = X + m_v - chroma;
        m_b = m_v - chroma;
    } else if (1 <= hue_prime && hue_prime < 2) {
        m_r = X + m_v - chroma;
        m_g = m_v;
        m_b = m_v - chroma;
    } else if (2 <= hue_prime && hue_prime < 3) {
        m_r = m_v - chroma;
        m_g = m_v;
        m_b = X + m_v - chroma;
    } else if (3 <= hue_prime && hue_prime < 4) {
        m_r = 0;
        m_g = X + m_v - chroma;
        m_b = m_v;
    } else if (4 <= hue_prime && hue_prime < 5) {
        m_r = X + m_v - chroma;
        m_g = m_v - chroma;
        m_b = m_v;
    } else if (5 <= hue_prime && hue_prime < 6) {
        m_r = m_v;
        m_g = m_v - chroma;
        m_b = X + m_v - chroma;
    } else {
        m_r = m_v - chroma;
        m_g = m_v - chroma;
        m_b = m_v - chroma;
    }
}

void color::set_RGB_from_CYMK() {
    m_r = 255 * (1-m_c/255.0) * (1-m_k/255.0);
    m_g = 255 * (1-m_m/255.0) * (1-m_k/255.0);
    m_b = 255 * (1-m_y/255.0) * (1-m_k/255.0);
}

void color::set_RGB_from_fRGB() {
    m_r = 255 * m_fr;
    m_g = 255 * m_fg;
    m_b = 255 * m_fb;
}

std::string remove_terminating_zeros(std::string str) {
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    str.erase(str.find_last_not_of('.') + 1, std::string::npos);
    return str;
}

std::string color::to_string() const {
    return ("(" + remove_terminating_zeros(std::to_string(m_r)) + ", " + remove_terminating_zeros(std::to_string(m_g)) + ", " + remove_terminating_zeros(std::to_string(m_b)) + ", " + remove_terminating_zeros(std::to_string(m_a)) + ")");
}

void color::print() const {
    std::cout << (*this).to_string() << std::endl;
}

#endif /* color_hpp */
