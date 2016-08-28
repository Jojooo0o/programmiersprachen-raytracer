#include "composite.hpp"
#include <iostream>

Composite::Composite()://Standard Constructer
	Shape(std::string("Composite"), std::string("")),
	shapes_() {}

Composite::Composite(std::string const& name, std::vector<std::shared_ptr<Shape>> const& shape):
	Shape(name, std::string("")),
	shapes_(shape) {}

void Composite::add_shape(std::shared_ptr<Shape> shape) {
	shapes_.push_back(shape);
} 

Hit Composite::intersect(Ray const& ray){
	Hit hi{};
	return hi;
}

std::ostream& Composite::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Objects: " << std::endl;
	for(auto it = shapes_.begin(); it != shapes_.end(); ++it){
		os << (**it) << std::endl;
	}

	return os;

}