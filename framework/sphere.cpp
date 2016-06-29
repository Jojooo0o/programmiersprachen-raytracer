#include "sphere.hpp"

Sphere::Sphere()://Constructor with console output
	Shape(std::string("Sphere"), Material{}),
	center_(glm::vec3{1.0f, 1.0f, 1.0f}),
	rad_(1.0f)
	{ std::cout << "Sphere::Constructor" << std::endl; }

//Custom constructor with console output
Sphere::Sphere(std::string const& name, Material const& material, glm::vec3 const& center, float rad):
	Shape(name, material),
	center_(center),
	rad_(rad){ std::cout << "Sphere::Constructor" << std::endl; }

//Desctructor
Sphere::~Sphere() { std::cout << "Sphere::Destructor" << std::endl; }

//getter
glm::vec3 const& Sphere::get_center() const{
	return center_;
}

float Sphere::get_radius() const{
	return rad_;
}
//oberflaeche
float Sphere::area() const {
	return rad_*rad_*M_PI*4;
}
//volumen
float Sphere::volume() const {
	return (4/3)*M_PI*rad_*rad_*rad_;
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
	return glm::intersectRaySphere(ray.origin, v, center_, rad_*rad_, distance);
}

