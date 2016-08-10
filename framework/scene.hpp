#ifndef SCENE_HPP
#define SCENE_HPP


#include <string>
#include <map>
#include <vector>
#include <memory>
#include "material.hpp"
#include "shape.hpp"

struct Scene
{
public:
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::map<std::string, Material> materials_;

};

void addMaterial(Scene& scene, Material const& mat){
	scene.materials_[mat.name_] = mat;

}

void addShape(Scene& scene, std::shared_ptr<Shape> const& shape){
	scene.shapes_.push_back(shape);
}


#endif

