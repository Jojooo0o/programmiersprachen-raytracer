#include "sdf_loader.hpp"


Material SDF_Loader::createMaterial(std::stringstream& line){
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

std::shared_ptr<Shape> SDF_Loader::createSphere(std::stringstream& line, Scene& sc){
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

std::shared_ptr<Shape> SDF_Loader::createBox(std::stringstream& line, Scene& sc){
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

Light SDF_Loader::createLight(std::stringstream& line){
	std::string word;
	std::string name;
	float x, y, z;

	line >> word; name = word;
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	glm::vec3 pos {x, y, z};
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	Color la {x, y, z};
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	Color ld {x, y, z};

	Light light(name, pos, la, ld);
	return light;
}

Camera SDF_Loader::createCamera(std::stringstream& line){
	std::string word;
	std::string name;
	float fov;

	line >> word; name = word;
	line >> word; fov = std::stof(word);

	glm::vec3 pos{0.0f, 0.0f, 0.0f};
	Camera cam(name, fov, pos);
	return cam;
}

Scene SDF_Loader::readInput(){
	
	Scene sc;

	std::string line;
	std::string word;
	std::ifstream file (input_);

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

					if (word == "sphere"){addShape(sc, createSphere(ss, sc));} 

					else if (word == "box"){addShape(sc, createBox(ss, sc));}

				} 

				else if (word == "light"){addLight(sc, createLight(ss));}

				else if (word == "camera"){addCamera(sc, createCamera(ss));} 
			} 

			else if (word == "render"){}
		}

		file.close();
	}

	return sc;
}

