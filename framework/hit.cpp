#include "hit.hpp"


Hit::Hit():
	hit_(false),
	distance_(0.0f),
	intersec_({0.0f, 0.0f, 0.0f}),
	normvec_({0.0f, 0.0f, 0.0f}),
	matname_("Material"),
	type_(""){}

Hit::Hit(bool hit, float distance, glm::vec3 const& intersec, glm::vec3 const& normvec, std::string const& mat, std::string const& type):
	hit_(hit),
	distance_(distance),
	intersec_(intersec),
	normvec_(normvec),
	matname_(mat),
	type_(type){}
