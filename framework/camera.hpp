#ifndef CAMERA
#define CAMERA

#include <glm/vec3.hpp>
#include <string>

class Camera{

public:

	Camera():
		name_("Camera"),
		fov_x_(0.0f),
		pos_({0.0f, 0.0f, 0.0f}){}

	Camera(std::string const& name, float fov, glm::vec3 const& pos):
		name_(name),
		fov_x_(fov),
		pos_(pos) {}

	std::string name_;
	float fov_x_;
	glm::vec3 pos_;

};

#endif