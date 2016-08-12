#include "hit.hpp"
#include "ray.hpp"
#include <iostream>

Hit::Hit():
	hit_(false),
	distance_(0.0f),
	intersec_({0.0f, 0.0f, 0.0f}),
	normvec_({0.0f, 0.0f, 0.0f}){}

Hit::Hit(bool hit, float distance, glm::vec3 const& intersec, glm::vec3 const& normvec):
	hit_(hit),
	distance_(distance),
	intersec_(intersec),
	normvec_(normvec){}

std::map<float, Hit> findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray){

	std::map<float, Hit> hits;
	float distance_temp;


	for(auto it = shapes.begin(); it != shapes.end(); it ++){
		Hit hit;
		hit.hit_ = (**it).intersect(ray, distance_temp);
		hit.distance_ = distance_temp;
		//TO BE CONTINUED

	}
 	
 	return hits;

}