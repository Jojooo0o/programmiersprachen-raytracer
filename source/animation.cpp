
#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <iostream>
#include <cmath>

#include "scene.hpp"
#include "sdf_loader.hpp"

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;

    std::string s = std::to_string(1);
    std::string ss = "../animation/try2/try" + s + ".ppm";
    std::string const filename = (ss);


    std::fstream new_txt;
    new_txt.open("../animation/try2/sdf.txt", std::ios::out);
    new_txt << "#CAMERAS" << std::endl;
    new_txt << std::endl;
    new_txt << "#define camera cam 30 0 -300 0 0 1 0 0 0 1" << std::endl;
    new_txt << "define camera cam 20 0 300 300 0 -300 -300 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 0 0 200 0 0 -1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 0 0 -300 0 0 1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 300 0 0 -1 0 0 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 -300 0 0 1 0 0 0 1 0 " << std::endl;
    new_txt << std::endl;
    new_txt << "#LIGHTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define light sun 200 1000 200 0.2 0.2 0.2 0.8 0.8 0.8 " << std::endl;
    new_txt << "define light light1 -200 1000 200 0.2 0.2 0.2 0.8 0.8 0.8 " << std::endl;
    new_txt << std::endl;
    new_txt << "#MATERIALS " << std::endl;
    new_txt << std::endl;
    new_txt << "define material red 1 0 0 1 0 0 1 0 0 10 0 0 0.2 " << std::endl;
    new_txt << "define material blue 0 0 1 0 0 1 0 0 1 0 0 0 0.2 " << std::endl;
    new_txt << "define material green 0 1 0 0 1 0 0 1 0 10 0 0 0.5 " << std::endl;
    new_txt << "define material gray 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0 0 0 1" << std::endl;
    new_txt << "define material orange 1 0.5 0 1 0.5 0 1 0.5 0 0 0 0 0" << std::endl;
    new_txt << std::endl;
    new_txt << "#OBJECTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define shape box base -100 -25 -100 100 -20 100 gray" << std::endl;
    new_txt << "define shape box box1 0 0 0 20 20 20 red" << std::endl;
    new_txt << std::endl;
    new_txt << "define shape sphere sphere1 0 0 0 10 green" << std::endl;
    new_txt << std::endl;  
    new_txt << "#COMPOSITE " << std::endl;
     new_txt << std::endl; 
    new_txt << "define shape composite mover sphere1 box1" << std::endl;
    new_txt << "#TRANSFORMATION " << std::endl;
    new_txt << std::endl;
    new_txt << "transform box1 translate 20 10 20 " << std::endl;
    new_txt << "transform mover translate 0 0 -30" << std::endl;
  

    new_txt.close();

  SDF_Loader input("../animation/try2/sdf.txt");
  Scene scene = input.readInput();

  Renderer app(width, height, filename, scene);

  std::thread thr([&app]() { app.render("cam"); });
  
  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }
  
  thr.join();


  return 0;
}
