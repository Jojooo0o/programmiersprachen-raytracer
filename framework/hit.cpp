#include "hit.hpp"
#include "ray.hpp"

Hit::Hit():
	hit_(false),
	distance_(0.0f),
	intersec_({0.0f, 0.0f, 0.0f}),
	normvec_({0.0f, 0.0f, 0.0f}){}

Hit::Hit(bool hit, float distance, glm::vec3 const& intersec, glm::vec3 const& normvec):
	hit_(hit),
	distance_(distance),
	intersec_(intersec),
	normvec_(normvec){}

//std::map<float, Hit> findHit(std::vector<shared_ptr<Shape>>, Ray)