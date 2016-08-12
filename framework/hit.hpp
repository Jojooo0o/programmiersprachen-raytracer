#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
#include <map>
#include <memory>

class Hit{

	Hit();
	Hit(bool, float, glm::vec3 const&, glm::vec3 const&);

	bool hit_;
	float distance_;
	glm::vec3 intersec_;
	glm::vec3 normvec_;
};

#endif