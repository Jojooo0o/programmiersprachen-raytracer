#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"
#include "material.hpp"

class Sphere: public Shape
{
public :
	Sphere();
	Sphere(std::string const&, Material const&, glm::vec3 const&, float);

	~Sphere();

	glm::vec3 const& get_center() const;
	float get_radius() const;

	float area() const override;
	float volume() const override;

	std::ostream& print(std::ostream&) const override;

	bool intersect (Ray const&, float&) override;

private :
	
	glm::vec3 center_;
	float rad_; 

};


#endif //BUW_SPHERE_HPP
