#include "shape.hpp"
#include <iostream>

Shape::Shape(): //Standard Constructor, with console output
	name_("Shape"),
	material_(Material{}) { std::cout << "Shape::Constructor" << std::endl; }

Shape::Shape(std::string const& name, Material const& material) : //custom constructor, wit console output
	name_(name),
	material_(material){ std::cout << "Shape::Constructor" << std::endl; }

Shape::~Shape() { std::cout << "Shape::Destructor" << std::endl; } //Destruktor

//getter
std::string const& Shape::get_name() const{
	return name_;
}

Material const& Shape::get_material() const{
	return material_;
}
//print
std::ostream& Shape::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Material: " << material_.name_ << ", " << material_.ka_ << ", " << material_.kd_ << ", " << material_.ks_ << ", " << material_.m_ << std::endl; 
	return os;
}
//operator
std::ostream& operator<<(std::ostream& os, Shape const& s){
	return s.print(os);
}

