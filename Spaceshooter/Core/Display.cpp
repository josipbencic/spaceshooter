#include "Display.hpp"

#include <cassert>
#include <iostream>

namespace loop_tools {

  Display::Display(int width, int height)
    : width(width), height(height) {

    p_display = al_create_display(width, height);
    assert(p_display != NULL);
  }

  Display::~Display() {
    al_destroy_display(p_display);
  }

  void Display::change_size(int _width, int _height) {

    if ( al_resize_display(p_display, _width, _height)) {
      width = _width;
      height = _height;
    }
    else {
      std::cout << "Failed to resize display" << std::endl;
    }
  }
}
