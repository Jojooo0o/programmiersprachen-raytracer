#include "sdf_loader.hpp"


Material SDF_Loader::createMaterial(std::stringstream& line){
	std::string name;
	std::string word;
	float r,g,b,m,t,eta,s;

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
	line >> word; t = std::stof(word);
	line >> word; eta = std::stof(word);
	line >> word; s = std::stof(word);


	Material mat {name, ka, kd, ks, m, t, eta, s};

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

	std::shared_ptr<Shape> p(new Sphere (name, center, rad, matname));

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

		std::shared_ptr<Shape> b(new Box (name, min, max, matname));

		return b;
}

std::shared_ptr<Shape> SDF_Loader::createComposite(std::stringstream& line, Scene& sc){
	std::string word;
	std::string name;
	std::string objectname;
	std::vector<std::shared_ptr<Shape>> objects;

	line >> word; name = word;
	while(line >> word){
		objectname = word;
		objects.push_back(sc.objects_[objectname]);
	}

	std::shared_ptr<Shape> composite(new Composite (name, objects));

	return composite;
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
	float fov, x, y, z;

	line >> word; name = word;
	line >> word; fov = std::stof(word);
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	glm::vec3 pos {x, y, z};
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	glm::vec3 dir {x, y, z};
	line >> word; x = std::stof(word);
	line >> word; y = std::stof(word);
	line >> word; z = std::stof(word);
	glm::vec3 up {x, y, z};

	Camera cam(name, fov, pos, dir, up);
	return cam;
}

void SDF_Loader::transform(std::stringstream& line, Scene& sc){
	std::string word;
	std::string name;
	float s, grad, x, y, z;

	line >> word; name = word;
	std::shared_ptr<Shape> shape = sc.objects_[name];

	line >> word;
	if(word == "scale"){
		line >> word; s = std::stof(word); 
		shape -> scale(s);
	} else if (word == "rotate"){
		line >> word; grad = std::stof(word);
		line >> word; x = std::stof(word);
		line >> word; y = std::stof(word);
		line >> word; z = std::stof(word);
		glm::vec3 r {x, y, z};
		shape -> rotate(grad, r);
	} else if (word == "translate"){
		line >> word; x = std::stof(word);
		line >> word; y = std::stof(word);
		line >> word; z = std::stof(word);
		glm::vec3 t {x, y, z};
		shape -> translate(t);
	}

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

					if ( word == "composite"){addObject(sc, createComposite(ss, sc));}

					else if (word == "sphere"){addShape(sc, createSphere(ss, sc));} 

					else if (word == "box"){addShape(sc, createBox(ss, sc));}

				} 

				else if (word == "light"){addLight(sc, createLight(ss));}

				else if (word == "camera"){addCamera(sc, createCamera(ss));} 
			} 
			else if (word == "transform"){transform(ss, sc);}

			else if (word == "render"){}
		}

		file.close();
	}

	return sc;
}

