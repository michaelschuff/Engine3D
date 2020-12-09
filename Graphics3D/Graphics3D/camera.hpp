//
//  camera.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/30/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "vector3.hpp"
#include "triangle.hpp"
#include "quaternion.hpp"

class scene;

class camera {
public:
    friend class scene;
private:
    vector3 m_position,
            m_forward = vector3(0, 0, 1),
            m_up = vector3(0, 1, 0),
            m_right = vector3(1, 0, 0),
            m_target = vector3(0, 0, 1);
    unsigned int m_width = 0,
                 m_height = 0;
    
    float m_fov = 3.14159/3,
          m_clipping_plane = 0.3,
          m_aspect_ratio = 1;
public:
    camera();
    camera(vector3 position,
           vector3 forward,
           vector3 up,
           vector3 right,
           float fov = 3.14159/3);
    
    void rotate(const quaternion&);
    void rotate(const vector3&, const float&);
    void look_at(const vector3&,
                 const vector3&);
    void set_position(const vector3&);
    
    char* get_view(const scene*) const;
private:
    quaternion reverse_camera_orientation;
    
    void update_reverse_camera_orientation();
};

#endif /* camera_hpp */
