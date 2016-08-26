#include "camera.hpp"

Camera::Camera():
		name_("Camera"),
		angle_(0.0f),
		distance_(0.0f),
		pos_({0.0f, 0.0f, 0.0f}){}

Camera::Camera(std::string const& name, float fov, glm::vec3 const& pos):
	name_(name),
	angle_(fov),
	distance_(0.0f),
	pos_(pos) {
		float rad = (angle_ * M_PI)/360;
		distance_ = 0.5/(std::tan(rad));
	}

Ray Camera::createRay(float x, float y) const{
	glm::vec3 vector {x, y, -distance_};
	glm::vec3 direction = vector - pos_;
	Ray ray{pos_, direction};
	return ray;
}

std::string Camera::get_name() const{
	return name_;
}

float Camera::get_angle() const{
	return angle_;
}

float Camera::get_distance() const{
	return distance_;
}

glm::vec3 Camera::get_pos() const{
	return pos_;
}