#ifndef SCENE_HPP
#define SCENE_HPP


#include <string>
#include <map>
#include <vector>
#include <memory>
#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "color.hpp"
#include "camera.hpp"

struct Scene
{
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<Light> lights_;
	std::map<std::string, Camera> cameras_;
	std::map<std::string, Material> materials_;
	Color ambient_ {0.0f, 0.0f, 0.0f};
};

void addMaterial(Scene& scene, Material const& mat){
	scene.materials_[mat.name_] = mat;

}

void addShape(Scene& scene, std::shared_ptr<Shape> const& shape){
	scene.shapes_.push_back(shape);
}

void addLight(Scene& scene, Light const& light){
	scene.lights_.push_back(light);
	scene.ambient_ += light.la_;
}

void addCamera(Scene& scene, Camera const& cam){
	scene.cameras_[cam.name_] = cam;
}


#endif
