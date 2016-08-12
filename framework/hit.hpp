#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
#include <map>
#include <memory>
#include <vector>

#include "scene.hpp"

class Hit{

public:

	Hit();
	Hit(bool, float, glm::vec3 const&, glm::vec3 const&);

	bool hit_;
	float distance_;
	glm::vec3 intersec_;
	glm::vec3 normvec_;
};

std::map<float, Hit> findHit(std::vector<std::shared_ptr<Shape>> const&, Ray const&);

#endif