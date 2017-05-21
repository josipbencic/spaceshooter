#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <allegro5/allegro.h>

namespace loop_tools {

  /*
    Wrapper class for Allegro's display.
  */
  class Display {
  public:

    Display(int width = 960, int height = 600);
    ~Display();

    /*
      Changing the screen's resolution.
    */
    void change_size(int width, int height);

    //  some getters
    inline ALLEGRO_DISPLAY* get_display() const {
      return p_display;
    }
    inline int get_width() const { return width; }
    inline int get_height() const  { return height; }

  private:
    ALLEGRO_DISPLAY* p_display;
    int width;
    int height;

    //  there will be no assign/copy
    Display(const Display&) {}
    Display& operator= (const Display&) {}
  };
}

#endif