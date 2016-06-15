#include "sphere.hpp"

Sphere::Sphere():
	Shape(std::string("Sphere"), Color{0.0f, 0.0f, 0.0f}),
	center_(glm::vec3{1.0f, 1.0f, 1.0f}),
	rad_(1.0f)
	{ std::cout << "Sphere::Constructor" << std::endl; }

Sphere::Sphere(std::string const& name, Color const& color, glm::vec3 const& center, float rad):
	Shape(name, color),
	center_(center),
	rad_(rad){ std::cout << "Sphere::Constructor" << std::endl; }

Sphere::~Sphere() { std::cout << "Sphere::Destructor" << std::endl; }

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

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	os << "Center: " << center_.x << ", " << center_.y << ", " << center_.z << std::endl;
	os << "Radius: " << rad_ << std::endl;
	return os;
}

bool Sphere::intersect (Ray const& ray, float& distance){
	auto v = glm::normalize(ray.direction);
	return glm::intersectRaySphere(ray.origin, v, center_, rad_*rad_, distance);
}

