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

void Hit::transformHit (glm::mat4 const& mat, glm::mat4 const& trans) {
	glm::vec4 intersec_4 {intersec_.x, intersec_.y, intersec_.z, 1.0f};
	glm::vec4 normvec_4 {normvec_.x, normvec_.y, normvec_.z, 0.0f};
	glm::vec3 temp(mat * intersec_4);
	intersec_ = temp;
	glm::vec3 tomp(mat * normvec_4);
	normvec_ = tomp;
}
