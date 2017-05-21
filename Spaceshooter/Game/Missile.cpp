#include "Missile.hpp"

#include "../Core/Display.hpp"

#include <allegro5/allegro_primitives.h>

using namespace std;
using namespace math;
using namespace loop_tools;


namespace sprites {

  Missile::Missile(
    vec3 pos,
    vec3 dir,
    const Display& display)
    : GameObject(pos, dir, true)
    , display(display)
    , time(al_get_time())
    , translation(1.0f)
  {}

  Missile::Missile(const Missile& rhs)
    : GameObject(rhs)
    , display(rhs.display)
    , time(al_get_time())
    , translation(rhs.translation)
  {}

  const Missile& Missile::operator= (const Missile& rhs) {

    is_alive = true;
    pos = rhs.pos;
    dir = rhs.dir;
    translation = rhs.translation;
    time = al_get_time();

    return *this;
  }

  void Missile::render() const {

    static const ALLEGRO_COLOR color = al_map_rgb(255,255,102);

    al_draw_filled_circle(pos.x, pos.y, 2, color);
  }

  void Missile::update() {

    double delta_time = al_get_time() - time;

    //  UPDATE MOVEMENTS
    translation = translate(delta_time * MISSILE_VELOCITY * dir);
    pos = translation * pos;

    is_alive = ( pos.x <= display.get_width() && pos.x >= 0.0f);

    time += delta_time;
  }

  const float StrongMissile::MISSILE_WIDTH = 33.0f;
  const float StrongMissile::MISSILE_HEIGHT = 15.0f;

  StrongMissile::StrongMissile(
    vec3 pos,
    vec3 dir,
    const Display& display,
    ALLEGRO_BITMAP* bmp)
    : Missile(pos, dir, display)
    , bmp(bmp)
  {}

  StrongMissile::StrongMissile(const StrongMissile& rhs)
    : Missile(rhs)
    , bmp(rhs.bmp)
  {}

  StrongMissile::~StrongMissile() {}

  void StrongMissile::render() const {

    al_draw_bitmap(bmp, pos.x, pos.y, 0);
  }


}
