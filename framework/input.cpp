#include "scene.hpp"

Scene readInput(std::string input){
	
	Scene sc;

	std::string word;
	std::ifstream file (input);

	if(file.is_open()){

		while(file >> word){			

			if(word == "define"){

				file >> word;

				if(word == "material"){ sc.addMaterial(createMaterial(file)); }

				else if (word == "shape"){} 

				else if (word == "light"){

				}
			} else if (word == "camera"){

			} else if (word == "render"){}
		}
		file.close();
	}

	return sc
}
