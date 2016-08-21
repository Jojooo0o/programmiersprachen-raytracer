#include "shape.hpp"
#include <iostream>

Shape::Shape():
	name_("Shape"),
	material_("material") {}

Shape::Shape(std::string const& name, std::string const& material) : 
	name_(name),
	material_(material){}


//getter
std::string const& Shape::get_name() const{
	return name_;
}

std::string const& Shape::get_material() const{
	return material_;
}
//print
std::ostream& Shape::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Material: " << material_ << std::endl; 
	return os;
}
//operator
std::ostream& operator<<(std::ostream& os, Shape const& s){
	return s.print(os);
}

