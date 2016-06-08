#include "box.hpp"

float Box::area() const  {
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

Box::Box():
	min_({0.0f, 0.0f, 0.0f}),
	max_({1.0f, 1.0f, 1.0f}){}

Box::Box(glm::vec3 a, glm::vec3 b):
	min_(a),
	max_(b){}


glm::vec3 const& Box::get_min() const{
	return min_;
}
glm::vec3 const& Box::get_max() const{
	return max_;
}