#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include "scene.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "sdf_loader.hpp"

TEST_CASE("sphere standardconstructor", "[sphere]"){
	Sphere sphere;
	std::cout << sphere << std::endl;

	REQUIRE(glm::all(glm::equal(sphere.get_center(), {1.0f, 1.0f, 1.0f})));
	REQUIRE(sphere.get_radius() == Approx(1.0f));
}

TEST_CASE("sphere custom constructor", "[sphere]"){
	Sphere sphere("sphere", {3.0f, 5.5f, -2.0f}, 10.0f, Material{});
	
	std::cout << sphere << std::endl;

	REQUIRE(glm::all(glm::equal(sphere.get_center(), {3.0f, 5.5f, -2.0f})));
	REQUIRE(sphere.get_radius() == Approx(10.0f));
}

TEST_CASE("box standardconstructor", "[box]"){
	Box box;
	std::cout << box << std::endl;

	REQUIRE(glm::all(glm::equal(box.get_min(), {0.0f, 0.0f, 0.0f})));
	REQUIRE(glm::all(glm::equal(box.get_max(), {1.0f, 1.0f, 1.0f})));
}

TEST_CASE("box custom constructor", "[box]"){
	Box box("box", {4.0f, 6.0f, -7.0f}, {2.0f, 7.0f, 8.0f}, Material{});
	std::cout << box << std::endl;

	REQUIRE(glm::all(glm::equal(box.get_min(), {2.0f, 6.0f, -7.0f})));
	REQUIRE(glm::all(glm::equal(box.get_max(), {4.0f, 7.0f, 8.0f})));
}

/*TEST_CASE("box intersect", "[raytracer]"){
	Box box("box", {5.0f, -1.0f, -1.0f}, {10.0f, 1.0f, 1.0f}, Material{});
	Ray ray {{0.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f}};
	float distance;
	
	REQUIRE(box.intersect(ray, distance));
	std::cout << "hi" << distance << std::endl;

}

TEST_CASE("box intersect2", "[raytracer]"){
	Box box;
	Ray ray {{-2.0f, 1.0f, 0.5f},{2.0f, -0.7f, 0.0f}};
	float distance;
	
	REQUIRE(box.intersect(ray, distance));
	std::cout << "hi" << distance << std::endl;

}

TEST_CASE("box intersect3", "[raytracer]"){
	Box box;
	Ray ray{{0.0f, 0.0f, 5.0f}, {-1.0f, 0.0f, 0.0f}};
	float direction;
	bool test = box.intersect(ray, direction);

	REQUIRE(test == false);

}*/

TEST_CASE("Scene", "[scene]"){
	std::map<std::string, Material> map;
	Material mat;
	Scene sc;
	addMaterial(sc, mat);
}

TEST_CASE("read sdf", "[raytracer]"){
	
	SDF_Loader input("../example.txt");
	Scene scene = input.readInput();


	std::map<std::string, Material> m = scene.materials_;
	std::vector<std::shared_ptr<Shape>> v = scene.shapes_;
	std::vector<Light> l = scene.lights_;
	std::map<std::string, Camera> c = scene.cameras_;

	for(std::map<std::string, Material>::iterator it = m.begin(); it != m.end(); it ++){
		std::cout << it->second << std::endl;
	}

	for(std::vector<std::shared_ptr<Shape>>::iterator it = v.begin(); it != v.end(); it ++){
		std::cout << **it << std::endl;
	}

	for(std::vector<Light>::iterator it = l.begin(); it != l.end(); it ++){
		std::cout << it -> name_ << std::endl;
	}

	std::cout << "Ambient: " << scene.ambient_ << std::endl;

	for(std::map<std::string, Camera>::iterator it = c.begin(); it != c.end(); it ++){
		std::cout << it->first << it -> second.get_distance() << std::endl;
	}

}



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
