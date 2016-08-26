#include "composite.hpp"

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
	Hit hi(false, 0.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, "");
	return hi;
}

std::ostream& Composite::print(std::ostream& os) const{
	std::cout << "Name: " << name_ << std::endl;
	std::cout << "Objects: " << std::endl;
	for(auto it = shapes_.begin(); it != shapes_.end(); it++){
		std::cout << "hai" << std::endl;
		std::cout << (*it)->get_name() << std::endl;
	}
}