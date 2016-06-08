#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <glm/vec3.hpp>
#include <cmath>

class Shape
{
public :

	virtual float area() const = 0;
	virtual float volume() const = 0;

private : 



};

#endif //BUW_SHAPE_HPP
