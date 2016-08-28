#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "shape.hpp"
#include "hit.hpp"


class Composite: public Shape
{
public:
	Composite();
	Composite(std::string const&, std::vector<std::shared_ptr<Shape>> const&);

	void add_shape(std::shared_ptr<Shape>);

	std::ostream& print(std::ostream&) const override;

	Hit intersect(Ray const&) override;

	void scale(float) override;
	void rotate(float, glm::vec3 const&) override;
	void translate(glm::vec3 const&) override;

private:
	std::vector<std::shared_ptr<Shape>> shapes_;

};


#endif //COMPOSITE_HPP