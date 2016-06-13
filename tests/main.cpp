#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <cmath>
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "sphere.hpp"
#include "box.hpp"


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


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
