#include "sphere.hpp"

float Sphere::area() const {
	return rad_*rad_*M_PI*4;
}

float Sphere::volume() const {
	return (4/3)*M_PI*rad_*rad_*rad_;
}

Sphere::Sphere():
	center_({1.0f, 1.0f, 1.0f}),
	rad_(1.0f) {}

Sphere::Sphere(glm::vec3 center_, float rad_):
	center_(center_),
	rad_(rad_) {}

glm::vec3 const& Sphere::get_center() const{
	return center_;
}

float Sphere::get_radius() const{
	return rad_;
}
