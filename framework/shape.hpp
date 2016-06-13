#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <glm/vec3.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include "color.hpp"

class Shape
{
public :

	Shape();
	Shape(std::string const&, Color const&);

	virtual float area() const = 0;
	virtual float volume() const = 0;

	std::string const& get_name () const;
	Color const& get_color() const;

	virtual std::ostream& print(std::ostream&) const;



protected : 
	
	std::string name_;
	Color color_;
	

};

std::ostream& operator<<(std::ostream&, Shape const&);

#endif //BUW_SHAPE_HPP