#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include "ray.hpp"

class Camera{

public:

	Camera();

	Camera(std::string const& name, float fov, glm::vec3 const& pos);

	Camera(std::string const& name, float fov, glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& up);

	Ray createRay(float, float);
	glm::mat4 createMatrix();

	std::string get_name() const;
	float get_angle() const;
	float get_distance() const;
	glm::vec3 get_pos() const;


private:

	std::string name_;
	float angle_;
	float distance_;	//distance to pixel canvas
	glm::vec3 pos_;
	glm::vec3 dir_;
	glm::vec3 up_;

};

#endif