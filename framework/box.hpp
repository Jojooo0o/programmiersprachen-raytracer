#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include "color.hpp"
#include <iostream>

class Box: public Shape
{
public :

	Box();
 	Box(std::string const&, Color const&, glm::vec3 const&, glm::vec3 const&);

	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;

	float area() const override;
	float volume() const override;

	std::ostream& print(std::ostream&) const override;

private :

	glm::vec3 min_;
	glm::vec3 max_;


};

std::ostream& operator<<(std::ostream&, Box const&);

#endif //BUW_BOX_HPP


