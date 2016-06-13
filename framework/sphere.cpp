#include "sphere.hpp"

Sphere::Sphere():
	Shape(std::string("Sphere"), Color{0.0f, 0.0f, 0.0f}),
	center_(glm::vec3{1.0f, 1.0f, 1.0f}),
	rad_(1.0f)
{}

Sphere::Sphere(std::string const& name, Color const& color, glm::vec3 const& center, float rad):
	Shape(name, color),
	center_(center),
	rad_(rad){}

glm::vec3 const& Sphere::get_center() const{
	return center_;
}

float Sphere::get_radius() const{
	return rad_;
}

float Sphere::area() const {
	return rad_*rad_*M_PI*4;
}

float Sphere::volume() const {
	return (4/3)*M_PI*rad_*rad_*rad_;
}
