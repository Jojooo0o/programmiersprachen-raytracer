#include "composite.hpp"
#include <iostream>

//Standard Constructer
Composite::Composite():
	Shape(std::string("Composite"), std::string("")),
	shapes_() {}

//Costum Constructor
Composite::Composite(std::string const& name, std::vector<std::shared_ptr<Shape>> const& shape):
	Shape(name, std::string("")),
	shapes_(shape) {}

//Adder
void Composite::add_shape(std::shared_ptr<Shape> shape) {
	shapes_.push_back(shape);
} 

//placeholder
Hit Composite::intersect(Ray const& ray){
	Hit hi{};
	return hi;
}

//printmethod
std::ostream& Composite::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Objects: " << std::endl;
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it){
		os << (**it) << std::endl;
	}

	return os;
}

//composite transformationation --> transform all children
void Composite::scale(float s){
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it){
		(**it).scale(s);
	}
}

void Composite::rotate(float grad, glm::vec3 const& r){
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it){
		(**it).rotate(grad, r);
	}
}

void Composite::translate(glm::vec3 const& t){
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it){
		(**it).translate(t);
	}

}