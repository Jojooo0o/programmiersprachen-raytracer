#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
#include <map>
#include <memory>
#include <vector>
#include "ray.hpp"


struct Hit{

	Hit();
	Hit(bool, float, glm::vec3 const&, glm::vec3 const&, std::string const&, std::string const&);

	void transformHit(glm::mat4 const&, glm::mat4 const&);

	bool hit_;
	float distance_;
	glm::vec3 intersec_;
	glm::vec3 normvec_;
	std::string matname_;
	std::string type_;
};


#endif