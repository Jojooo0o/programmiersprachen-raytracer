#include "sphere.hpp"

Sphere::Sphere()://Constructor with console output
	Shape(std::string("Sphere"), Material{}),
	center_(glm::vec3{1.0f, 1.0f, 1.0f}),
	rad_(1.0f) {}

//Custom constructor with console output
Sphere::Sphere(std::string const& name, glm::vec3 const& center, float rad, Material const& material):
	Shape(name, material),
	center_(center),
	rad_(rad){}

//getter
glm::vec3 const& Sphere::get_center() const{
	return center_;
}

float Sphere::get_radius() const{
	return rad_;
}

//Printmethode
std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	os << "Center: " << center_.x << ", " << center_.y << ", " << center_.z << std::endl;
	os << "Radius: " << rad_ << std::endl;
	return os;
}
//gibt true false aus, wenn strahl kugel schneidet oder nicht
//setzt float auf abstand zwischen strahlstartpunkt u kugel
bool Sphere::intersect (Ray const& ray, float& distance){
	return glm::intersectRaySphere(ray.origin, ray.direction, center_, rad_*rad_, distance);
}

