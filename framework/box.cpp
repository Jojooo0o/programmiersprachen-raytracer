#include "box.hpp"
#include <iostream>

Box::Box():
	Shape(std::string("Box"), {0.0f, 0.0f, 0.0f}),
	min_({0.0f, 0.0f, 0.0f}),
	max_({1.0f, 1.0f, 1.0f}) {}


Box::Box(std::string const& name, Color const& color, glm::vec3 const& a, glm::vec3 const& b):
	Shape(name, color),
	min_(a),
	max_(b) {}

float Box::area() const {
	float x = abs(max_.x - min_.x);
	float y = abs(max_.y - min_.y);
	float z = abs(max_.z - min_.z);

	float a = x*y;
	float b = x*z;
	float c = y*z;

	return 2*(a+b+c);
}

float Box::volume() const {
	float x = abs(max_.x - min_.x);
	float y = abs(max_.y - min_.y);
	float z = abs(max_.z - min_.z);

	return x*y*z;
}


glm::vec3 const& Box::get_min() const{
	return min_;
}
glm::vec3 const& Box::get_max() const{
	return max_;
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Min: " << min_.x << ", " << min_.y << ", " << min_.z << std::endl;
	os << "Max: " << max_.x << ", " << max_.y << ", " << max_.z << std::endl;
	return os;
}
