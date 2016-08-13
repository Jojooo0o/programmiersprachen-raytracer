#include "scene.hpp"


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
	scene.cameras_[cam.get_name()] = cam;
}