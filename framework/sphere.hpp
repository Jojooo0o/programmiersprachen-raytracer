#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include "shape.hpp"

class Sphere: public Shape
{
public :
	Sphere();
	Sphere(glm::vec3, float);

	glm::vec3 const& get_center() const;
	float get_radius() const;

	float area() const override;
	float volume() const override;

private :
	
	glm::vec3 center_;
	float rad_; 

};

#endif //BUW_SPHERE_HPP
