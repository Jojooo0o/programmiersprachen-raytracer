#include "sphere.hpp"
#include <catch.hpp>

Sphere::Sphere()://Constructor with console output
	Shape(std::string("Sphere"), std::string("material")),
	center_(glm::vec3{1.0f, 1.0f, 1.0f}),
	rad_(1.0f) {}

//Custom constructor with console output
Sphere::Sphere(std::string const& name, glm::vec3 const& center, float rad, std::string const& material):
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
Hit Sphere::intersect (Ray const& original_ray){
	Ray ray = original_ray.transformRay(inv_);
	ray.direction = glm::normalize(ray.direction);
	float distance;
	glm::vec3 intersec, normvec;
	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, rad_ * rad_, distance);

	if(hit){
		intersec = ray.origin + ray.direction * distance;
		normvec = glm::normalize(intersec - center_);

		Hit hi (hit, distance, intersec, normvec, material_, "sphere");
		hi.transformHit(world_transform_, trans_inv_);
		return hi;
	} else {
		Hit hi{};
		return hi;
	}
}

