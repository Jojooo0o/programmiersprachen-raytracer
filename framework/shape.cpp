#include "shape.hpp"
#include <iostream>

Shape::Shape():
	name_("Shape"),
	material_("material"),
	world_transform_(glm::mat4(1.0f)) {}

Shape::Shape(std::string const& name, std::string const& material) : 
	name_(name),
	material_(material),
	world_transform_(glm::mat4(1.0f)){}


//getter
std::string const& Shape::get_name() const{
	return name_;
}

std::string const& Shape::get_material() const{
	return material_;
}

//transformation
void Shape::scale(float s){
	glm::vec3 scaleVec (s, s, s);
	glm::mat4 scalingMat = glm::scale(scaleVec);
	world_transform_ = scalingMat * world_transform_;
}

void Shape::rotate(float grad, glm::vec3 const& r){
	glm::mat4 rotationMat = glm::rotate(grad, r);
	world_transform_ = rotationMat * world_transform_;
}

void Shape::translate(glm::vec3 const& t){
	glm::mat4 translateMat = glm::translate(t);
	world_transform_ = translateMat * world_transform_;
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



