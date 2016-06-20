#include "shape.hpp"
#include <iostream>

Shape::Shape(): //Standard Constructor, with console output
	name_("Shape"),
	color_({0.0f, 0.0f, 0.0f}) { std::cout << "Shape::Constructor" << std::endl; }

Shape::Shape(std::string const& name, Color const& color) : //custom constructor, wit console output
	name_(name),
	color_(color){ std::cout << "Shape::Constructor" << std::endl; }

Shape::~Shape() { std::cout << "Shape::Destructor" << std::endl; } //Destruktor

//getter
std::string const& Shape::get_name() const{
	return name_;
}

Color const& Shape::get_color() const{
	return color_;
}
//print
std::ostream& Shape::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Color: " << color_.r << ", " << color_.g << ", " << color_.b << ", " << std::endl; 
	return os;
}
//operator
std::ostream& operator<<(std::ostream& os, Shape const& s){
	return s.print(os);
}
