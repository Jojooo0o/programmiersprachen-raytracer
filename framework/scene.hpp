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
#include "box.hpp"
#include "sphere.hpp"
#include "composite.hpp"

struct Scene
{
	std::vector<std::shared_ptr<Shape>> shapes_;	//intersect-container
	std::vector<Light> lights_;
	std::map<std::string, Camera> cameras_;
	std::map<std::string, Material> materials_;
	std::map<std::string, std::shared_ptr<Shape>> objects_;		//transformation-container
	Color ambient_ {0.0f, 0.0f, 0.0f};
};

void addMaterial(Scene&, Material const&);

void addShape(Scene&, std::shared_ptr<Shape> const&);

void addLight(Scene&, Light const&);

void addCamera(Scene&, Camera const&);

void addObject(Scene&, std::shared_ptr<Shape> const&);


#endif
