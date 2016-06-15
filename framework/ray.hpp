#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(glm::vec3 const& origin, glm::vec3 const& direction): 
		origin(origin), 
		direction(direction) {}

	Ray(): 
		origin({0.0f, 0.0f, 0.0f}), 
		direction({0.0f, 1.0f, 0.0f}) {}

};

#endif