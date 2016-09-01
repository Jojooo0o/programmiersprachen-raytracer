
#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <iostream>

#include "scene.hpp"
#include "sdf_loader.hpp"

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;

  for(int i=0; i<= 5; i++){
    std::string s = std::to_string(i);
    std::string ss = "../animation/test" + s + ".ppm";
    std::string const filename = (ss);
    //Erstellung der txt
    //Veränderung der txt

    std::fstream new_txt;
    int x = i * 10;
    new_txt.open("../animation/animation_try1.txt", std::ios::out);
    new_txt << "define camera cam 20 0 300 " << x <<" 0 -1 0 0 0 -1" << std::endl;
    new_txt << "#CAMERAS" << std::endl;
    new_txt << std::endl;
    new_txt << "define camera cam 20 0 300 0 0 -1 0 0 0 -1 " << std::endl;
    new_txt << "#define camera cam 20 0 -300 0 0 1 0 0 0 -1 " << std::endl;
    new_txt << "#define camera cam 20 0 0 300 0 0 -1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 0 0 -300 0 0 1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 300 0 0 -1 0 0 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 -300 0 0 1 0 0 0 1 0 " << std::endl;
    new_txt << std::endl;
    new_txt << "#LIGHTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define light sun3 0 1000 0 0.2 0.2 0.2 0.8 0.8 0.8 " << std::endl;
    new_txt << std::endl;
    new_txt << "#MATERIALS " << std::endl;
    new_txt << std::endl;
    new_txt << "define material red 1 0 0 1 0 0 1 0 0 10 0 0 0.5 " << std::endl;
    new_txt << "define material blue 0 0 1 0 0 1 0 0 1 100 0 0 0 " << std::endl;
    new_txt << "define material green 0 1 0 0 1 0 0 1 0 10 0 0 0.2 " << std::endl;
    new_txt << std::endl;
    new_txt << "#OBJECTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define shape sphere sphere -30 0 0 100 green " << std::endl;
    new_txt << std::endl;
    new_txt << "#TRANSFORMATION " << std::endl;
    new_txt << std::endl;
    new_txt << "transform sphere rotate " << x << " 0 1 0 " << std::endl;
    new_txt << "#transform sphere scale 2 " << std::endl;
    new_txt << "#transform sphere translate 10 5 0 " << std::endl;
    new_txt << "new_txt.close(); " << std::endl;

  SDF_Loader input("../animation/animation_try1.txt");
  Scene scene = input.readInput();

  Renderer app(width, height, filename, scene);

  std::thread thr([&app]() { app.render("cam"); });
  
  /*Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }
  */
  thr.join();
  }

  return 0;
}
