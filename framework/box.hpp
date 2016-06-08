#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"

class Box: public Shape
{
public :

	Box();
	Box(glm::vec3, glm::vec3);

	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;

private :

	glm::vec3 min_;
	glm::vec3 max_;


};

#endif //BUW_BOX_HPP
