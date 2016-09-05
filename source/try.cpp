
#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <iostream>
#include <cmath>

#include "scene.hpp"
#include "sdf_loader.hpp"

int main(int argc, char* argv[])
{
  unsigned const width = 1000;
  unsigned const height = 800;

  for(int i=0; i<= 400; i++){
    std::string s = std::to_string(i);
    std::string ss = "../animation/try1/try" + s + ".ppm";
    std::string const filename = (ss);
    //Erstellung der txt
    //Veränderung der txt

    std::fstream new_txt;
    double counter = (double)i;
    double scalecounter = 540*counter / 400;
    double scalebox = 0.5 + std::abs(sin(M_PI * scalecounter/ 180));
    int rotatesphere = i;
    double scale = 0.8;
    int zoom = 200;
    double grad = counter/3 + 40;
    double rad = (grad * M_PI)/180;
    double cammove_x, cammove_y, cammove_z;
    cammove_x = 300 * sin((counter/360)*M_PI);
    cammove_y = 200 * sin(rad);
    cammove_z = 200 * cos(rad);
    //if ( i > 10 && i < 20){
    //zoom += i*20;
    //}
    new_txt.open("../animation/try1/sdf.txt", std::ios::out);
    new_txt << "#CAMERAS" << std::endl;
    new_txt << std::endl;
    new_txt << "define camera cam 30 "<< cammove_x << " " << cammove_y << " " << cammove_z << " " << -cammove_x << " " << -cammove_y << " " << -cammove_z << " " << -cammove_x << " " << 1000 -cammove_y << " " << -cammove_z << std::endl;
    new_txt << "#define camera cam 90 0 300 0 0 -1 0 0 0 1 " << std::endl;
    new_txt << "#define camera cam 20 0 0 200 0 0 -1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 0 0 -300 0 0 1 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 300 0 0 -1 0 0 0 1 0 " << std::endl;
    new_txt << "#define camera cam 20 -300 0 0 1 0 0 0 1 0 " << std::endl;
    new_txt << std::endl;
    new_txt << "#LIGHTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define light sun -200 700 0 0.2 0.2 0.2 0.8 0.8 0.8 " << std::endl;
    new_txt << std::endl;
    new_txt << "#MATERIALS " << std::endl;
    new_txt << std::endl;
    new_txt << "define material red 1 0 0 1 0 0 1 0 0 10 0 0 0.2 " << std::endl;
    new_txt << "define material blue 0 0 1 0 0 1 0 0 1 100 0 0 0.2 " << std::endl;
    new_txt << "define material green 0 1 0 0 1 0 0 1 0 10 0 0 0.2 " << std::endl;
    new_txt << "define material white 1 1 1 1 1 1 1 1 1 0 0 0 1" << std::endl;
    new_txt << "define material gray 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0 0 0 1" << std::endl;
    new_txt << "define material darkgray 0.08 0.08 0.08 0.08 0.08 0.08 0.08 0.08 0.08 0 0 0 1" << std::endl;
    new_txt << "define material yellow 1 0.8 0 1 0.8 0 1 0.8 0 0 0 0 0.5" << std::endl;
    new_txt << "define material orange 1 0.5 0 1 0.5 0 1 0.5 0 0 0 0 0.5" << std::endl;
    new_txt << std::endl;
    new_txt << "#OBJECTS " << std::endl;
    new_txt << std::endl;
    new_txt << "define shape box base -1000 -110 -1000 1000 -100 1000 gray" << std::endl;
    new_txt << "define shape box spinbox -5 -5 -5 5 5 5  yellow" << std::endl;
    //new_txt << "define shape box spinbox2 -100 -5 -5 -95 5 5  orange" << std::endl;
    new_txt << std::endl;
    new_txt << "define shape sphere ground 0 -200 0 160 darkgray" << std::endl;
    new_txt << "define shape sphere sphere1 -30 0 0 7 blue " << std::endl;
    new_txt << "define shape sphere sphere2 0 -30 0 7 green " << std::endl;
    new_txt << "define shape sphere sphere3 0 0 -30 7 red " << std::endl;
    new_txt << std::endl;
    new_txt << "#TRANSFORMATION " << std::endl;
    new_txt << std::endl;
    new_txt << "transform spinbox scale " << scalebox << std::endl;
    new_txt << "transform sphere1 rotate " << rotatesphere << " 0 1 0 " << std::endl;
    new_txt << "transform sphere2 rotate " << rotatesphere << " 0 0 1 " << std::endl;
    new_txt << "transform sphere3 rotate " << rotatesphere << " 1 0 0 " << std::endl;
    new_txt << "transform spinbox rotate " << rotatesphere << " 1 1 1 " << std::endl;
   	//new_txt << "transform spinbox2 rotate " << 90 << " 1 1 0 " << std::endl;
    //new_txt << "transform spinbox2 scale " << scale << std::endl;

    new_txt.close();

  SDF_Loader input("../animation/try1/sdf.txt");
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
