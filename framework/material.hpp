#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>
#include "color.hpp"

struct Material
{
  Material(std::string name, color ka, color kd, color ks,  float m) :
  name_(name), 
  ka_(ka), 
  kd_(kd),
  ks_(ks),
  m_(m) {}

  std::string name_;
  color ka_;
  color kd_;
  color ks_;
  float m_;



  friend std::ostream& operator<<(std::ostream& os, Material const& mat)
  {
    os << "(" << mat.name_ << "," << mat.ka_ << "," << mat.kd_ << "," << mat.ks_ << "," << mat.m_")\n";
    return os;
  }

};

#endif //#define BUW_COLOR_HPP