#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"


class Light{

public:

	Light():
		name_("Light"),
		position_({0.0f, 0.0f, 0.0f}),
		la_({0.0f, 0.0f, 0.0f}),
		ld_({0.0f, 0.0f, 0.0f}) {}

	Light(std::string const& name, glm::vec3 const& pos, Color const& la, Color const& ld) :
		name_(name),
		position_(pos),
		la_(la),
		ld_(ld){}

	std::string name_;
	glm::vec3 position_;
	Color la_;
	Color ld_;

};

#endif