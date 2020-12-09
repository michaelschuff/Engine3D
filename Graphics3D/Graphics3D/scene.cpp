//
//  scene.cpp
//  Graphics3D
//
//  Created by Michael Schuff on 12/3/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#include "scene.hpp"

scene::scene() : triangles(std::vector<triangle>()),
                 meshes(std::vector<mesh>()) {
    
}

scene::scene(const std::vector<mesh>& t_meshes,
             const camera& main_cam) :
                triangles(std::vector<triangle>()),
                meshes(t_meshes),
                main_camera(main_cam) {
    
}

scene::scene(const std::vector<triangle>& t_triangles,
             const camera& main_cam) :
                triangles(t_triangles),
                meshes(std::vector<mesh>()),
                main_camera(main_cam) {
    
}

char* scene::get_view() const {
    return main_camera.get_view(this);
}

char* camera::get_view(const scene* world) const {
    char* pixels = new char[4 * m_width * m_height];
    
    std::vector<triangle> triangles;
    
    for (triangle tri: world->triangles) {
        triangles.push_back((tri - m_position) * reverse_camera_orientation);
    }
    
    for (mesh m: world->meshes) {
        m -= m_position;
        m *= reverse_camera_orientation;
        copy(m.triangles.begin(), m.triangles.end(), back_inserter(triangles));
    }
    
    return pixels;
}
