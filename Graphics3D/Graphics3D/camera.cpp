//
//  camera.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 11/30/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "camera.hpp"

camera::camera() {
        
}

camera::camera(vector3 position,
               vector3 forward,
               vector3 up,
               vector3 right,
               float fov) :
                m_position(position),
                m_forward(forward),
                m_up(up),
                m_right(right),
                m_fov(fov) {
    update_reverse_camera_orientation();
}

void camera::update_reverse_camera_orientation() {
    quaternion f_to_z = get_quaternion(m_forward,
                                       vector3(0, 0, 1));
    reverse_camera_orientation = f_to_z * get_quaternion(m_up.rotated(f_to_z),
                                                         vector3(0, 1, 0));
}

void camera::rotate(const quaternion& q) {
    m_position.rotate(q);
    m_forward.rotate(q);
    m_up.rotate(q);
    m_right.rotate(q);
    update_reverse_camera_orientation();
}

void camera::rotate(const vector3 &axis, const float& theta) {
    m_position.rotate(axis, theta);
    m_forward.rotate(axis, theta);
    m_up.rotate(axis, theta);
    m_right.rotate(axis, theta);
    update_reverse_camera_orientation();
}

void camera::look_at(const vector3& target, const vector3& up) {
    m_forward = target - m_position;
    m_up = up;
    m_right = cross_product(m_up, m_forward);
    update_reverse_camera_orientation();
}

void camera::set_position(const vector3& position) {
    m_position = position;
}
