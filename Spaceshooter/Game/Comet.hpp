#ifndef COMET_HPP
#define COMET_HPP

#include "../Game/GameObject.hpp"
#include "../Game/GameConstants.hpp"

#include "../Math/mat3.hpp"
#include "../Math/vec3.hpp"

namespace loop_tools {
  class Display;
}

namespace sprites {

  class Comet :
    public GameObject {

  public:
    /*
      Ctor
        - doesnt's load bitmap (it gets the pointer)
          - bitmap contains whole animation
        - initializes direction 
    */
    Comet(	
      math::vec3 pos,
      ALLEGRO_BITMAP*	img,
      const loop_tools::Display&	display);

    /*
      Sets comet dead after it passes the screen.
      Updates its coordinates and animation frame.
    */
    void update();
    
    /*
      Renders current part of animation bitmap.
      If the frame time has passed, it switches to a next one.
    */
    void render() const;

    int damage() const {
      return COMET_DAMAGE;
    }

    int score() const {
      return COMET_SCORE;
    }

    math::vec3 AABB_min() const {
      return math::vec3(pos.x - BOUND, pos.y - BOUND, 1.0f);
    }

    math::vec3 AABB_max() const {
      return math::vec3(pos.x + BOUND, pos.y  + BOUND, 1.0f);
    }

  private:


    math::mat3    translation;

    double        time;

    //  animation and bitmap vars
    int               current_frame;
    double            frame_count;
    double            frame_delay;
    ALLEGRO_BITMAP*   img;


    //  Game logic variables and
    //  variables that describe animation resources
    const float       BOUND; 
    const float       FRAME_WIDTH;
    const float       FRAME_HEIGHT;

    static const int  MAX_FRAME = 143;
    static const int  ANIMATION_COLUMNS = 21;
  };
}

#endif // COMET_HPP_INCLUDED
