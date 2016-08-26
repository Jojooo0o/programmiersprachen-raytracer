#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "scene.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "light.hpp"
#include "camera.hpp"

class SDF_Loader{

public:

	SDF_Loader(): input_("nofile"){}
	SDF_Loader(std::string const& input): input_(input){}

	Scene readInput();

	Material createMaterial(std::stringstream&);
	std::shared_ptr<Shape> createSphere(std::stringstream& line, Scene& sc);
	std::shared_ptr<Shape> createBox(std::stringstream& line, Scene& sc);
	Light createLight(std::stringstream& line);
	Camera createCamera(std::stringstream& line);
	std::shared_ptr<Shape> createComposite(std::stringstream& line, Scene& sc);
	Scene readInput(std::string input);


private:

	std::string input_;
};

#endif