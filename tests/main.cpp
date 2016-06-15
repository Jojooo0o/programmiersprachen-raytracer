#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include <iostream>


//AUFGABE 2
TEST_CASE("sphere", "[aufgabe 2]"){
	Sphere s1;
	std::string name2 = "sphere";
	glm::vec3 center_s2{2.0f, 5.1f, -3.4f};
	glm::vec3 center_s1{1.0f, 1.0f, 1.0f};
	Color black{0.0f, 0.0f, 0.0f};
	Color red{1.0f, 0.0f, 0.0f};
	Sphere s2{name2, red, center_s2, 2.0f};
	
	REQUIRE(glm::all(glm::equal(s1.get_center(), center_s1)));
	REQUIRE(s1.get_color() == black);
	REQUIRE(s1.get_name() == "Sphere");
	REQUIRE(s1.get_radius() == Approx(1.0f));
	REQUIRE(s1.area() == Approx(1*1*M_PI*4));
	REQUIRE(s1.volume() == Approx((4/3)*M_PI*1*1*1));

	REQUIRE(glm::all(glm::equal(s2.get_center(), center_s2)));
	REQUIRE(s2.get_color() == red);
	REQUIRE(s2.get_name() == "sphere");
	REQUIRE(s2.get_radius() == Approx(2.0f));
	REQUIRE(s2.area() == Approx(2*2*M_PI*4));
	REQUIRE(s2.volume() == Approx((4/3)*M_PI*2*2*2));

}
//AUFGABE 5
	TEST_CASE("box", "[aufgabe 2]"){
		Box b1;
		glm::vec3 b1_min{0.0f, 0.0f, 0.0f};
		glm::vec3 b1_max{1.0f, 1.0f, 1.0f};
		glm::vec3 b2_min{2.0f, 4.0, 2.0f};
		glm::vec3 b2_max{4.0f, 2.0f, 4.0f};
		Color black{0.0f, 0.0f, 0.0f};
		Color red{1.0f, 0.0f, 0.0f};
		std::string name2 = "box";
		Box b2 {name2, red, b2_min, b2_max};

		REQUIRE(glm::all(glm::equal(b1.get_min(), b1_min)));
		REQUIRE(glm::all(glm::equal(b1.get_max(), b1_max)));
		REQUIRE(b1.get_color()== black);
		REQUIRE(b1.get_name() == "Box");
		REQUIRE(b1.area() == Approx(6.0f));
		REQUIRE(b1.volume() == Approx(1.0f));

		REQUIRE(glm::all(glm::equal(b2.get_min(), b2_min)));
		REQUIRE(glm::all(glm::equal(b2.get_max(), b2_max)));
		REQUIRE(b2.get_color() == red);
		REQUIRE(b2.get_name() == "box");
		REQUIRE(b2.area() == Approx(24.0f));
		REQUIRE(b2.volume() == Approx(8.0f));
	}


	TEST_CASE("print", "[aufgabe 4]"){
		std::string name1 = "box";
		std::string name2 = "sphere";
		Color red{1.0f, 0.0f, 0.0f};
		glm::vec3 b1_min{0.0f, 0.0f, 0.0f};
		glm::vec3 b1_max{1.0f, 1.0f, 1.0f};
		glm::vec3 center_s1{1.0f, 1.0f, 1.0f};
		Box b1 {name1, red, b1_min, b1_max};
		Sphere s1{name2, red, center_s1, 2.0f};

		std::cout << s1;
		std::cout << b1;
	}

//AUFGABE 6
	TEST_CASE("intersectRaySphere", "[intersect]"){
		//Ray
		glm::vec3 ray_origin{0.0, 0.0, 0.0};
		//ray direction has to be normalized!
		//you can use:
		//v = glm::normalize(some_vector)
		glm::vec3 ray_direction{0.0, 0.0, 1.0};

		//Sphere
		glm::vec3 sphere_center{0.0, 0.0, 5.0};
		float sphere_radius{1.0};

		float distance{0.0};
		auto result = glm::intersectRaySphere(
			ray_origin, ray_direction, sphere_center, sphere_radius*sphere_radius, distance);
		REQUIRE(distance == Approx(4.0f));
	}

	TEST_CASE("intersect", "[aufgabe 6]"){

		Ray r1;
		std::string name2 = "sphere";
		Color red{1.0f, 0.0f, 0.0f};
		glm::vec3 center_s1{0.0, 5.0, 0.0};
		Sphere s1{name2, red, center_s1, 6.0f};
		float distance{0.0f};

		auto result = s1.intersect(r1, distance);

		REQUIRE(result);
		REQUIRE(distance == Approx(11.0f));
	}

//AUFGABE 7
	TEST_CASE("example", "[aufgabe 7 ]"){
		Color red(255, 0, 0);
		glm::vec3 position(0.0, 0.0, 0.0);

		std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>("sphere0", red, position, 1.2f);
		std::shared_ptr<Shape> s2 = std::make_shared<Sphere>("sphere1", red, position, 1.2f);

		s1->print(std::cout);
		s2->print(std::cout);
	}

//AUFGABE 8
	TEST_CASE("virtual", "[aufgabe 8 ]"){

		std::cout << "--------------------------------------------" << std::endl;
		Color red(255, 0, 0);
		glm::vec3 position(0.0, 0.0, 0.0);

		Sphere* s1 = new Sphere("sphere0", red, position, 1.2f);
		Shape* s2 = new Sphere("sphere1", red, position, 1.2f);

		s1->print(std::cout);
		s2->print(std::cout);

		delete s1;
		delete s2;
	}




int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
