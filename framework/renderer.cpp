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
      int maxRecursion = 5;
      
      //transform pixel coordinates to camera coordinates     

      float x1 = ((float)x - half_width)/width;
      float y1 = ((float)y - half_height)/width;

      Ray camRay = cam.createRay(x1, y1);
      Color color = raytrace(camRay, maxRecursion);
      /*Hit camHit = findHit(scene_.shapes_, camRay);

      if(camHit.hit_ == false){
        color = scene_.ambient_;
      } else {

        //auto it = camHits.begin();
        //Hit firstHit = it->second;
        Material mat = scene_.materials_[camHit.matname_];

        color.r += mat.ka_.r * scene_.ambient_.r; 
        color.g += mat.ka_.g * scene_.ambient_.g;
        color.b += mat.ka_.b * scene_.ambient_.b;

        for(auto it = scene_.lights_.begin(); it != scene_.lights_.end(); ++ it){
          glm::vec3 lightVec = (*it).position_ - camHit.intersec_; 
          lightVec = glm::normalize(lightVec);


          Ray lightRay;
          if(camHit.type_ == "sphere"){
            lightRay = {camHit.intersec_+ 0.01f * lightVec, lightVec};
          } else if(camHit.type_ == "box"){
            lightRay = {(camHit.intersec_ + 0.01f * lightVec), lightVec};
          }
          Hit lightHits = findHit(scene_.shapes_, lightRay);

          glm::vec3 spec_light = glm::reflect(lightVec, camHit.normvec_);
          float r_v_ = pow(glm::dot(glm::normalize(camRay.direction), glm::normalize(spec_light)), mat.m_);  //Spiegelende Reflexion

          if(mat.s > 0.0f){
            glm::vec3 object_reflect = glm::reflect(camRay.direction, camHit.normvec_);
            Ray reflectionRay{camHit.intersec_, object_reflect};

          }


          

        //Shadows
          if(!lightHits.hit_){
            
            color.r += mat.kd_.r * (*it).ld_.r * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.r * r_v_);
            color.g += mat.kd_.g * (*it).ld_.g * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.g * r_v_);
            color.b += mat.kd_.b * (*it).ld_.b * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.b * r_v_);
          }
        }
      }*/


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


/*std::map<float, Hit> findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray){

  std::map<float, Hit> hits;

  for(auto it = shapes.begin(); it != shapes.end(); it ++){
    Hit hit = (**it).intersect(ray);
    if (hit.hit_){
     hits[hit.distance_] = hit;
    }

  }
  
  return hits;

}*/

Hit findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray){

  Hit firstHit{};
  firstHit.distance_ = 100000000.0f;

  for(auto it = shapes.begin(); it != shapes.end(); it ++){
    Hit hit = (**it).intersect(ray);
    if (hit.hit_){
      hit.distance_ = glm::distance(hit.intersec_, ray.origin);
      if(firstHit.distance_ > hit.distance_){
        firstHit = hit;
      }
    }

  }
  
  return firstHit;

}

Color Renderer::raytrace(Ray const& ray, int maxRecursion){

  maxRecursion --;
  Color color{};
  Hit camHit = findHit(scene_.shapes_, ray);

      if(camHit.hit_ == false){
        color = scene_.ambient_;
      } else {

        //auto it = camHits.begin();
        //Hit firstHit = it->second;
        Material mat = scene_.materials_[camHit.matname_];

        color.r += mat.ka_.r * scene_.ambient_.r; 
        color.g += mat.ka_.g * scene_.ambient_.g;
        color.b += mat.ka_.b * scene_.ambient_.b;

        for(auto it = scene_.lights_.begin(); it != scene_.lights_.end(); ++ it){
          glm::vec3 lightVec = (*it).position_ - camHit.intersec_; 
          lightVec = glm::normalize(lightVec);


          Ray lightRay;
          if(camHit.type_ == "sphere"){
            lightRay = {camHit.intersec_+ 0.01f * lightVec, lightVec};
          } else if(camHit.type_ == "box"){
            lightRay = {(camHit.intersec_ + 0.01f * lightVec), lightVec};
          }
          Hit lightHits = findHit(scene_.shapes_, lightRay);

          glm::vec3 spec_light = glm::reflect(lightVec, camHit.normvec_);
          float r_v_ = pow(glm::dot(glm::normalize(ray.direction), glm::normalize(spec_light)), mat.m_);  //Spiegelende Reflexion

          if(!lightHits.hit_){
              
              color.r += mat.kd_.r * (*it).ld_.r * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.r * r_v_);
              color.g += mat.kd_.g * (*it).ld_.g * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.g * r_v_);
              color.b += mat.kd_.b * (*it).ld_.b * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.b * r_v_);
            }
          }


           if(maxRecursion > 0){ 
            if(mat.s_ > 0.0f){
                glm::vec3 object_reflect = glm::reflect(ray.direction, camHit.normvec_);
                glm::normalize(object_reflect);
                Ray reflectionRay{camHit.intersec_+ 0.01f * object_reflect, object_reflect};
                Color reflectedCol = raytrace(reflectionRay, maxRecursion);

                //color = color * (1.0f - mat.s_);
                color +=  mat.s_ * reflectedCol;

            }

          
           /* if(mat.t_ > 0.0f){
              //glm::vec3 refraction = glm::refract(ray.direction, camHit.normvec_, mat.eta_);
              //Ray refractionRay{camHit.intersec_ + 0.01f * refraction, refraction};
              Ray new_ray{camHit.intersec_ + 0.001f * ray.direction, ray.direction};
              Color refractedCol = raytrace(new_ray, maxRecursion);
              color = ((1.0f - mat.t_) * color) + (mat.t_ * refractedCol);
            }*/
          }
        }

        return color;
  }