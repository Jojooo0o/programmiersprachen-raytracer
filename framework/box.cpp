#include "box.hpp"
#include <iostream>
#include <catch.hpp>

Box::Box(): //Standard Constructor
	Shape(std::string("Box"), std::string("material")),
	min_({0.0f, 0.0f, 0.0f}),
	max_({1.0f, 1.0f, 1.0f}) {}

//Custom Constructor
Box::Box(std::string const& name, glm::vec3 const& a, glm::vec3 const& b, std::string const& material):
	Shape(name, material),
	min_(a),
	max_(b) 
	{
		if (min_.x > max_.x){
			auto help = min_.x;
			min_.x = max_.x;
			max_.x = help;
		}
		if (min_.y > max_.y){
			auto help = min_.y;
			min_.y = max_.y;
			max_.y = help;
		}
		if (min_.z > max_.z){
			auto help = min_.z;
			min_.z = max_.z;
			max_.z = help;
		}
	
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

Hit Box::intersect (Ray const& original){
	Ray ray = original.transformRay(inv_);
	float t0, t1;
	float tnear = 0.0f;
	float tfar = 0.0f;
	bool hit = true;
	float distance = -1;
	glm::vec3 normvec;
	glm::vec3 intersec;
	Hit hi{};

	// {0,0,0} abfangen
	if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0) {return hi;}

	if (ray.direction.x != 0.0f)
	{
		t0 = (min_.x - ray.origin.x) / ray.direction.x;
		t1 = (max_.x - ray.origin.x) / ray.direction.x;
		tfar = std::max(t0,t1);
		tnear = std::min(t0,t1);

		if (tnear > tfar)
		{
			return hi;
		}

	} else {

		if(min_.x > ray.origin.x || max_.x < ray.origin.x) {return hi;}
	}

	if (ray.direction.y != 0.0f)
	{
		t0 = (min_.y - ray.origin.y) / ray.direction.y;
		t1 = (max_.y - ray.origin.y) / ray.direction.y;
		tnear = std::max(tnear, std::min(t0,t1));
		tfar = std::min(tfar, std::max(t0,t1));

		
		if (tnear > tfar)
		{
			return hi;
		}

	} else {

		if(min_.y > ray.origin.y || max_.y < ray.origin.y) {return hi;}
	}

	if (ray.direction.z != 0.0f)
	{
		t0 = (min_.z - ray.origin.z) / ray.direction.z;
		t1 = (max_.z - ray.origin.z) / ray.direction.z;
		tnear = std::max(tnear, std::min(t0,t1));
		tfar = std::min(tfar, std::max(t0,t1));
		
		if (tnear > tfar)
		{
			return hi;
		}

	} else {

		if(min_.z > ray.origin.z || max_.z < ray.origin.z) {return hi;}
	}

	if(tnear < 0.0) {return hi;}
	
	intersec = ray.origin + ray.direction * tnear;

	if(intersec.x == Approx(min_.x)) {normvec = {-1.0f, 0.0f, 0.0f};}
	else if (intersec.x == Approx(max_.x)) {normvec = {1.0f, 0.0f, 0.0f};}
	else if (intersec.y == Approx(min_.y)) {normvec = {0.0f, -1.0f, 0.0f};}
	else if (intersec.y == Approx(max_.y)) {normvec = {0.0f, 1.0f, 0.0f};}
	else if (intersec.z == Approx(min_.z)) {normvec = {0.0f, 0.0f, -1.0f};}
	else if (intersec.z == Approx(max_.z)) {normvec = {0.0f, 0.0f, 1.0f};}

	hi.hit_ = hit;
	hi.distance_ = tnear;
	hi.intersec_ = intersec;
	hi.normvec_ = normvec;
	hi.matname_ = material_;
	hi.type_ = "box";
	hi.transformHit(world_transform_, trans_inv_);
	
	return hi;


}
