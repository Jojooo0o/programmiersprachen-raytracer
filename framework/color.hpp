// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>


//modified standard Color
struct Color
{
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  Color() : r(0.0f), g(0.0f), b(0.0f) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator*(Color const& col, float factor)
  {
    float r = col.r*factor;
    float g = col.g*factor;
    float b = col.b*factor;
    Color color{r, g, b};
    return color;
  }

  friend Color operator*(float factor, Color const& col)
  {
    float r = col.r*factor;
    float g = col.g*factor;
    float b = col.b*factor;
    Color color{r, g, b};
    return color;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend bool operator == (Color const& a, Color const& b)
  {
    return((a.r == b.r)&&(a.g == b.g)&&(a.b == b.b));
  }
};

#endif //#define BUW_COLOR_HPP
