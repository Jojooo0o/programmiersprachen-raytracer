#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(glm::vec3 const& origin, glm::vec3 const& direction): 
		origin(origin), 
		direction(glm::normalize(direction)) {}

	Ray(): 
		origin({0.0f, 0.0f, 0.0f}), 
		direction({1.0f, 1.0f, 1.0f}) {
			direction = glm::normalize(direction);
		}

	Ray transformRay(glm::mat4 const& mat){

		glm::vec4 origin4(origin.x, origin.y, origin.z, 1.0f);
		glm::vec4 direction4(direction.x, direction.y, direction.z, 0.0f);
		glm::vec4 origin_trans = mat * origin4;
		glm::vec4 direction_trans = mat * direction4;

		glm::vec3 origin3(origin_trans);
		glm::vec3 direction3(direction_trans);

		Ray ray;
		ray.origin = origin3;
		ray.direction = direction3;

		return ray;
	}

};

#endif