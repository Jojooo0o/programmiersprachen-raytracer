#include "box.hpp"
#include <iostream>

Box::Box(): //Standard Constructor
	Shape(std::string("Box"), Material{}),
	min_({0.0f, 0.0f, 0.0f}),
	max_({1.0f, 1.0f, 1.0f}) {}

//Custom Constructor
Box::Box(std::string const& name, Material const& material, glm::vec3 const& a, glm::vec3 const& b):
	Shape(name, material),
	min_(a),
	max_(b) 
	{
		if (min_.x > max.x){
			auto help = min_.x;
			min_.x = max_.x;
			max_.x = help;
		}
		if (min_.y > max.y){
			auto help = min_.y;
			min_.y = max_.y;
			max_.y = help;
		}
		if (min_.z > max.z){
			auto help = min_.z;
			min_.z = max_.z;
			max_.z = help;
		}
	
	}
//Oberflächeninhalt
float Box::area() const {
	float x = abs(max_.x - min_.x);
	float y = abs(max_.y - min_.y);
	float z = abs(max_.z - min_.z);

	float a = x*y;
	float b = x*z;
	float c = y*z;

	return 2*(a+b+c);
}
//Volumensberechnung
float Box::volume() const {
	float x = abs(max_.x - min_.x);
	float y = abs(max_.y - min_.y);
	float z = abs(max_.z - min_.z);

	return x*y*z;
}

//Getter
glm::vec3 const& Box::get_min() const{
	return min_;
}
glm::vec3 const& Box::get_max() const{
	return max_;
}
//Printmethode
std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Min: " << min_.x << ", " << min_.y << ", " << min_.z << std::endl;
	os << "Max: " << max_.x << ", " << max_.y << ", " << max_.z << std::endl;
	return os;
}

bool Box::intersect (Ray const& ray, float& distance){
	float tnear,tfar;
	distance = -1;

	if (ray.direction_.x != 0.0)
	{
		float t0 = (min_.x - ray.origin_.x) / ray.direction_.x;
		float t1 = (max_.x - ray.origin_.x) / ray.direction_.x;
		tfar = std::max(t0,t1);
		tnear = std::min(t0,t1);
	}
	else 
	{
		if(min_.x > ray.origin_.x || max_.x < ray.origin_.x) {return false;}
	}

	if (ray.direction_.y != 0.0)
	{
		float t0 = (min_.y - ray.origin_.y) / ray.direction_.y;
		float t1 = (max_.y - ray.origin_.y) / ray.direction_.y;
		float tnear = std::max(tnear, std::min(t0,t1));
		float tfar = std::min(tfar, std::max(t0,t1));
		if (tnear > tfar)
		{
			return false;
		}
	}
	else 
	{
		if(min_.y > ray.origin_.y || max_.y < ray.origin_.y) {return false;}
	}

	if (ray.direction_.z != 0.0)
	{
		float t0 = (min_.z - ray.origin_.z) / ray.direction_.z;
		float t1 = (max_.z - ray.origin_.z) / ray.direction_.z;
		tnear = std::max(tnear, std::min(t0,t1));
		tfar = std::min(tfar, std::max(t0,t1));
		if (tnear > tfar)
		{
			return false;
		}
	}
	else 
	{
		if(min_.z > ray.origin_.z || max_.z < ray.origin_.z) {return false;}
	}

	distance = tnear*sqrt(ray.direction_.x*ray.direction_.x +
					      ray.direction_.y*ray.direction_.y +
					      ray.direction_.z*ray.direction_.z);
	return true;
}
