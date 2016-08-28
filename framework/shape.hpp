#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"

class Shape
{
public :

	Shape();
	Shape(std::string const&, std::string const&);


	std::string const& get_name () const;
	std::string const& get_material() const;
	glm::mat4 const& get_matrix() const;

	virtual Hit intersect(Ray const&) = 0;

	virtual void scale(float);
	virtual void rotate(float, glm::vec3 const&);
	virtual void translate(glm::vec3 const&);

	virtual std::ostream& print(std::ostream&) const;



protected : 
	
	std::string name_;
	std::string material_;
	glm::mat4 world_transform_;
	glm::mat4 trans_inv_;
	glm::mat4 inv_;

};

std::ostream& operator<<(std::ostream&, Shape const&);

#endif //BUW_SHAPE_HPP

/*TODO:
-INVERSE
-TRANSPONIERTE INVERSE
-COMPOSITE
-SDF LOADER

*/