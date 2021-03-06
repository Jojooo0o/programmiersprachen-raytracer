// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "ray.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "hit.hpp"
#include <string>
#include <glm/glm.hpp>
#include <map>
#include <iostream>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void render(std::string const&); //Added
  void write(Pixel const& p);

  Color raytrace(Ray const&, int); //Added


  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_; //Added
};


  Hit findHit(std::vector<std::shared_ptr<Shape>> const&, Ray const&);


#endif // #ifndef BUW_RENDERER_HPP
