// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(scene)
{}

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , scene_()
{}

void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else { 
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(std::string const& cam_name){

  Camera cam = scene_.cameras_[cam_name];
  float width = (float)width_;      
  float half_height = ((float)height_) / 2;
  float half_width = ((float)width_) / 2;

  for(unsigned y = 0; y < height_; ++y){
    for (unsigned x = 0; x < width_; ++x){
      Pixel p(x,y);
      Color color{};
      
      //transform pixel coordinates to camera coordinates     

      float x1 = ((float)x - half_width)/width;
      float y1 = ((float)y - half_height)/width;

      Ray camRay = cam.createRay(x1, y1);
      std::map<float, Hit> camHits = findHit(scene_.shapes_, camRay);

      if(camHits.empty()){
        color = scene_.ambient_;
      } else {

        auto it = camHits.begin();
        Hit firstHit = it->second;
        Material mat = scene_.materials_[firstHit.matname_];

        for(auto it = scene_.lights_.begin(); it != scene_.lights_.end(); ++ it){
          glm::vec3 lightVec = (*it).position_ - firstHit.intersec_; 
          lightVec = glm::normalize(lightVec);

          Ray lightRay {(firstHit.intersec_ + 0.0001f * lightVec), lightVec};
          std::map<float, Hit> lightHits = findHit(scene_.shapes_, lightRay);

          

        //Shadows
          if(lightHits.empty()){
            
            color.r += mat.ka_.r * (*it).la_.r + mat.kd_.r * (*it).ld_.r * glm::dot(firstHit.normvec_, lightRay.direction);
            color.g += mat.ka_.g * (*it).la_.g + mat.kd_.g * (*it).ld_.g * glm::dot(firstHit.normvec_, lightRay.direction);
            color.b += mat.ka_.b * (*it).la_.b + mat.kd_.b * (*it).ld_.b * glm::dot(firstHit.normvec_, lightRay.direction);
          } else {
            color.r += mat.ka_.r * (*it).la_.r; 
            color.g += mat.ka_.g * (*it).la_.g;
            color.b += mat.ka_.b * (*it).la_.b;
          }

        }
      }
      p.color = color;
      write(p);
      
    }
  }

}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}


std::map<float, Hit> findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray){

  std::map<float, Hit> hits;

  for(auto it = shapes.begin(); it != shapes.end(); it ++){
    Hit hit = (**it).intersect(ray);
    if (hit.hit_){
     hits[hit.distance_] = hit;
    }

  }
  
  return hits;

}
