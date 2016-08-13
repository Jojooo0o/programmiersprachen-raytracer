#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <glm/vec3.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"

class Shape
{
public :

	Shape();
	Shape(std::string const&, Material const&);


	std::string const& get_name () const;
	Material const& get_material() const;

	virtual Hit intersect(Ray const&) = 0;

	virtual std::ostream& print(std::ostream&) const;



protected : 
	
	std::string name_;
	Material material_;
	

};

std::ostream& operator<<(std::ostream&, Shape const&);

#endif //BUW_SHAPE_HPP