//
//  scene.hpp
//  Graphics3D
//
//  Created by Michael Schuff on 12/3/20.
//  Copyright © 2020 Michael Schuff. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include <stdio.h>
#include <vector>
#include "vector3.hpp"
#include "triangle.hpp"
#include "mesh.hpp"
#include "camera.hpp"

class scene {
public:
    std::vector<triangle> triangles;
    std::vector<mesh> meshes;
    camera main_camera;
    
    scene();
    scene(const std::vector<mesh>& t_meshes,
          const camera& main_cam = camera());
    scene(const std::vector<triangle>& t_meshes,
          const camera& main_cam = camera());
    
    char* get_view() const;
};

#endif /* scene_hpp */
