#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <memory>
#include "scene.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "sdf_loader.hpp"
#include "hit.hpp"
#include "renderer.hpp"
#include "composite.hpp"

TEST_CASE("sphere standardconstructor", "[sphere]"){
	Sphere sphere;
	std::cout << sphere << std::endl;

	REQUIRE(glm::all(glm::equal(sphere.get_center(), {1.0f, 1.0f, 1.0f})));
	REQUIRE(sphere.get_radius() == Approx(1.0f));
}

TEST_CASE("sphere custom constructor", "[sphere]"){
	Sphere sphere("sphere", {3.0f, 5.5f, -2.0f}, 10.0f, "black");
	
	std::cout << sphere << std::endl;

	REQUIRE(glm::all(glm::equal(sphere.get_center(), {3.0f, 5.5f, -2.0f})));
	REQUIRE(sphere.get_radius() == Approx(10.0f));
}

TEST_CASE("sphere intersect", "[hi]"){
	Sphere sphere;
	Ray ray{};
	float distance;

	Hit hit = sphere.intersect(ray);

	REQUIRE(hit.hit_);
}

TEST_CASE("box standardconstructor", "[box]"){
	Box box;
	std::cout << box << std::endl;

	REQUIRE(glm::all(glm::equal(box.get_min(), {0.0f, 0.0f, 0.0f})));
	REQUIRE(glm::all(glm::equal(box.get_max(), {1.0f, 1.0f, 1.0f})));
}

TEST_CASE("box custom constructor", "[box]"){
	Box box("box", {4.0f, 6.0f, -7.0f}, {2.0f, 7.0f, 8.0f}, "flieder");
	std::cout << box << std::endl;

	REQUIRE(glm::all(glm::equal(box.get_min(), {2.0f, 6.0f, -7.0f})));
	REQUIRE(glm::all(glm::equal(box.get_max(), {4.0f, 7.0f, 8.0f})));
}

TEST_CASE("box intersect", "[raytracer]"){
	Box box("box", {5.0f, -1.0f, -1.0f}, {10.0f, 1.0f, 1.0f}, "soulblack");
	Ray ray {{0.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f}};
	Hit hit = box.intersect(ray);

	REQUIRE(hit.hit_);

	std::cout << "hi" << hit.distance_ << std::endl;

}

TEST_CASE("box intersect2", "[raytracer]"){
	Box box;
	Ray ray {{-2.0f, 1.0f, 0.5f},{2.0f, -0.7f, 0.0f}};
	Hit hit = box.intersect(ray);
	REQUIRE(hit.hit_);
	std::cout << "hi" << hit.distance_ << std::endl;

}

TEST_CASE("box intersect3", "[raytracer]"){
	Box box;
	Ray ray{{0.0f, 0.0f, 5.0f}, {-1.0f, 0.0f, 0.0f}};
	Hit hit = box.intersect(ray);

	REQUIRE(!hit.hit_);

}

TEST_CASE("Scene", "[scene]"){
	std::map<std::string, Material> map;
	Material mat;
	Scene sc;
	addMaterial(sc, mat);
}

/*TEST_CASE("read sdf", "[raytracer]"){
	
	SDF_Loader input("../example.txt");
	Scene scene = input.readInput();


	std::map<std::string, Material> m = scene.materials_;
	std::vector<std::shared_ptr<Shape>> v = scene.shapes_;
	std::vector<Light> l = scene.lights_;
	std::map<std::string, Camera> c = scene.cameras_;
	std::map<std::string, std::shared_ptr<Shape>> object = scene.objects_;

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
	
	std::cout << "Objects" << std::endl;
	for(auto it = object.begin(); it != object.end(); it ++){
		std::shared_ptr<Shape> derp = it -> second;
		std::cout << *derp << std::endl;
	}
	
}*/
TEST_CASE("composite", "[composite]"){
	std::shared_ptr<Shape> box(new Box ());
	std::shared_ptr<Shape> sphere(new Sphere ());
	std::vector<std::shared_ptr<Shape>> p;

	p.push_back(box);
	p.push_back(sphere);

	Composite comp("Test", p);

	std::cout << comp << std::endl;

	comp.rotate(90.0, {1.0f, 0.0f, 0.0f});
	auto mat = box->get_matrix();

	for(int i = 0; i != 4; i ++){
		glm::vec4 v (mat[i]);
		std::cout << v.x << " , " << v.y << " , " << v.z << " , " << v.w << std::endl;

	}

}

TEST_CASE("shape", "[World transform]"){
	Sphere sphere;
	//sphere.scale(2.0f);
	sphere.rotate(90.0, {1.0f, 0.0f, 0.0f});
	auto mat = sphere.get_matrix();


	for(int i = 0; i != 4; i ++){
		glm::vec4 v (mat[i]);
		std::cout << v.x << " , " << v.y << " , " << v.z << " , " << v.w << std::endl;

	}

}

TEST_CASE("transform", "[matrix]"){
	Sphere sphere;
	glm::vec4 point (0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec3 axis (1.0f, 0.0f, 0.0f);
	sphere.scale(2.0f);
	//sphere.rotate(90.0f, axis);
	sphere.translate({1.0f, 0.0f, 0.0f});

	point = sphere.get_matrix() * point;
	glm::vec3 transformed(point);
	std::cout << transformed.x << " , " << transformed.y << " , " << transformed.z << std::endl;
}


/*TEST_CASE("findHit", "[hit]"){
	std::shared_ptr<Shape> s1(new Sphere ("s1", {0.0f, 0.0f, 0.0f}, 1.0f, "black"));
	std::shared_ptr<Shape> s2(new Sphere ("s2", {2.0f, 0.0f, 0.0f}, 1.0f, "black"));
	std::shared_ptr<Shape> s3(new Sphere ("s3", {4.0f, 0.0f, 0.0f}, 1.0f, "black"));

	std::vector<std::shared_ptr<Shape>> vec;
	vec.push_back(s1);
	vec.push_back(s2);
	vec.push_back(s3);

	Ray ray {{-2.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};

	std::map<float, Hit> hit  = findHit(vec, ray);

	std::cout << "hello" << std::endl;

	for(auto it = hit.begin(); it != hit.end(); it ++){
		std::cout << "hi";
		std::cout << it->first << std::endl;
	}

	bool bla = true;

	for(auto it = hit.begin(); it != hit.end(); it ++){
		bla = it->second.hit_;
	}

	REQUIRE(bla);

}*/

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
