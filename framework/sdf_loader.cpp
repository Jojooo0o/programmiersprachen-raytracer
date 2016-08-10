#include <iostream>
#include <fstream>
#include <sstream>
#include "scene.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

Material createMaterial(std::stringstream& line){
	std::string name;
	std::string word;
	float r,g,b,m;

	line >> word; name = word;

	line >> word; r = std::stof(word);
	line >> word; g = std::stof(word);
	line >> word; b = std::stof(word);
	Color ka {r,g,b};

	line >> word; r = std::stof(word);
	line >> word; g = std::stof(word);
	line >> word; b = std::stof(word);
	Color kd {r,g,b};

	line >> word; r = std::stof(word);
	line >> word; g = std::stof(word);
	line >> word; b = std::stof(word);
	Color ks {r,g,b};

	line >> word; m = std::stof(word);

	Material mat {name, ka, kd, ks, m};

	return mat;

}

std::shared_ptr<Shape> createSphere(std::stringstream& line, Scene& sc){
	std::string word;
	std::string name;
	std::string matname;
	float x, y, z, rad;

	line >> word; name = word;
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	glm::vec3 center {x, y, z};
	line >> word; rad = std::stof(word);
	line >> word; matname = word;

	std::shared_ptr<Shape> p(new Sphere (name, center, rad, sc.materials_[matname]));

	return p;

}

std::shared_ptr<Shape> createBox(std::stringstream& line, Scene& sc){
		std::string word;
		std::string name;
		std::string matname;
		float x, y, z;

		line >> word; name = word;
		line >> word; x = std::stof(word);
		line >> word; y = std::stof(word);
		line >> word; z = std::stof(word);
		glm::vec3 min {x, y, z};
		line >> word; x = std::stof(word);
		line >> word; y = std::stof(word);
		line >> word; z = std::stof(word);
		glm::vec3 max {x, y, z};
		line >> word; matname = word;

		std::shared_ptr<Shape> b(new Box (name, min, max, sc.materials_[matname]));

		return b;

}

Scene readInput(std::string input){
	
	Scene sc;

	std::string line;
	std::string word;
	std::ifstream file (input);

	if(file.is_open()){

		while(std::getline(file, line)){
			std::stringstream ss;
			ss << line;	
			ss >> word;		

			if(word == "define"){

				ss >> word;

				if(word == "material"){addMaterial(sc, createMaterial(ss)); }

				else if (word == "shape"){
					ss >> word;
					if (word == "sphere"){
						addShape(sc, createSphere(ss, sc));
					} else if (word == "box"){
						addShape(sc, createSphere(ss, sc));
					}
				} 

				else if (word == "light"){

				}
			} else if (word == "camera"){

			} else if (word == "render"){}
		}
		file.close();
	}

	return sc;
}

