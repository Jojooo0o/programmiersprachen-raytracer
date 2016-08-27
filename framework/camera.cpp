#include "camera.hpp"

Camera::Camera():
		name_("Camera"),
		angle_(0.0f),
		distance_(0.0f),
		pos_({0.0f, 0.0f, 0.0f}),
		dir_({0.0f, 0.0f, -1.0f}),
		up_({0.0f, 1.0f, 0.0f}){}

Camera::Camera(std::string const& name, float fov, glm::vec3 const& pos):
	name_(name),
	angle_(fov),
	distance_(0.0f),
	pos_(pos),
	dir_({0.0f, 0.0f, -1.0f}),
	up_({0.0f, 1.0f, 0.0f}) {
		float rad = (angle_ * M_PI)/360;
		distance_ = 0.5/(std::tan(rad));
	}

Camera::Camera(std::string const& name, float fov, glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& up):
	name_(name),
	angle_(fov),
	distance_(0.0f),
	pos_(pos),
	dir_(dir),
	up_(up) {
		float rad = (angle_ * M_PI)/360;
		distance_ = 0.5/(std::tan(rad));
	}

glm::mat4 Camera::createMatrix() {
	glm::vec3 u = glm::cross(dir_, up_);
	glm::vec3 v = glm::cross(u, dir_);

	u = glm::normalize(u);
	v = glm::normalize(v);
	dir_ = glm::normalize(dir_);

	glm::vec4 u4(u.x, u.y, u.z, 0.0f);
	glm::vec4 v4(v.x, v.y, v.z, 0.0f);
	glm::vec4 dir_4(-dir_.x, -dir_.y, -dir_.z, -0.0f);
	glm::vec4 pos_4(pos_.x, pos_.y, pos_.z, 1.0f);
	glm::mat4 c(u4, v4, dir_4, pos_4);
	//glm::mat4 c;
	//c[0] = u4;
	//c[1] = v4;
	//c[2] = dir_4;
	//c[3] = pos_4;

	return c;
}

Ray Camera::createRay(float x, float y){
	//glm::vec4 vector {x, y, -distance_, 0.0f};
	glm::vec3 origin {0.0f, 0.0f, 0.0f};
	glm::vec3 direction {x, y, -distance_};
	//vector = createMatrix() * vector;
	//glm::vec3 direction {vector.x, vector.y, vector.z};
	Ray ray{origin, direction};
	Ray transformed = ray.transformRay(createMatrix());
	return transformed;
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

