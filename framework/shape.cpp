#include "shape.hpp"
#include <iostream>

//Standard Constructor
Shape::Shape():
	name_("Shape"),
	material_("material"),
	world_transform_(glm::mat4(1.0f)),
	inv_(glm::mat4(1.0f)),
	trans_inv_(glm::mat4(1.0f)) {}

//Costum Constructor
Shape::Shape(std::string const& name, std::string const& material) : 
	name_(name),
	material_(material),
	world_transform_(glm::mat4(1.0f)),
	inv_(glm::inverse(world_transform_)),
	trans_inv_(glm::transpose(inv_)) {}


//getter
std::string const& Shape::get_name() const{
	return name_;
}

std::string const& Shape::get_material() const{
	return material_;
}

glm::mat4 const& Shape::get_matrix() const{
	return world_transform_;
}

//transformation
void Shape::scale(float s){
	glm::vec3 scaleVec (s, s, s);
	glm::mat4 scalingMat = glm::scale(scaleVec);
	world_transform_ = scalingMat * world_transform_;
	inv_ = glm::inverse(world_transform_); 
	trans_inv_ = glm::transpose(inv_);
}

void Shape::rotate(float grad, glm::vec3 const& r){
	float rad = (grad * M_PI)/180;
	glm::mat4 rotationMat = glm::rotate(rad, r);
	world_transform_ = rotationMat * world_transform_;
	inv_ = glm::inverse(world_transform_); 
	trans_inv_ = glm::transpose(inv_);
}

void Shape::translate(glm::vec3 const& t){
	glm::mat4 translateMat = glm::translate(t);
	world_transform_ = translateMat * world_transform_;
	inv_ = glm::inverse(world_transform_); 
	trans_inv_ = glm::transpose(inv_);
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



