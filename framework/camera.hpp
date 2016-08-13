#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>
#include <cmath>

class Camera{

public:

	Camera();

	Camera(std::string const& name, float fov, glm::vec3 const& pos);

	glm::vec3 createRay(float, float) const;

	std::string get_name() const;
	float get_angle() const;
	float get_distance() const;
	glm::vec3 get_pos() const;


private:

	std::string name_;
	float angle_;
	float distance_;	//distance to pixel canvas
	glm::vec3 pos_;

};

#endif