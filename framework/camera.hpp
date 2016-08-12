#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>
#include <cmath>

class Camera{

public:

	Camera():
		name_("Camera"),
		angle_(0.0f),
		distance_(0.0f),
		pos_({0.0f, 0.0f, 0.0f}){}

	Camera(std::string const& name, float fov, glm::vec3 const& pos):
		name_(name),
		angle_(fov),
		distance_(0.0f),
		pos_(pos) {
			float rad = (angle_ * M_PI)/360;
			distance_ = 0.5/(std::tan(rad));
		}

	std::string name_;
	float angle_;
	float distance_;	//distance to pixel canvas
	glm::vec3 pos_;

};

#endif