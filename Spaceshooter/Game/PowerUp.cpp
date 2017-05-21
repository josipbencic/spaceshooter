#include "PowerUp.hpp"

#include "../Math/math2d.hpp"

#include "../Core/Display.hpp"

#include "../Game/GameConstants.hpp"
#include "../Game/Spaceship.hpp"
#include "../Game/Missile.hpp"

using namespace loop_tools;
using namespace math;


namespace sprites {

  void get_health_powerup(Spaceship& ship) {
    ship.set_health(ship.get_health() + POWERUP_HEALTH_AMOUNT);
  }

  void get_double_powerup(Spaceship& ship) {
    ship.set_current_missile_type(MissileType::DOUBLE);
    ship.reset_power_up_timer(POWERUP_DOUBLE_DURATION);
  }

  void get_strong_powerup(Spaceship& ship) {
    ship.set_current_missile_type(MissileType::STRONG_GREEN);
    ship.reset_power_up_timer(POWERUP_STRONG_DURATION);
  }

  const float PowerUp::FRAME_RADIUS = 30.0f;

  PowerUp::PowerUp(
    const Display& dsp,
    vec3 pos,
    ALLEGRO_BITMAP* img_,
    void (*get_effect_func)(Spaceship&))
  : GameObject(pos, vec3(-1.0f, 0.0f, 0.0f), true)
  , time(al_get_time())
  , frame_count(0.0)
  , rotation_angle(0.0f)
  , img(img_)
  , get_effect(NULL) {

    assert(get_effect_func != NULL);
    get_effect = get_effect_func;
  }

  PowerUp::PowerUp(const PowerUp& src)
    : GameObject(src)
    , time(al_get_time())
    , frame_count(0.0)
    , rotation_angle(0.0f)
    , img(src.img)
    , get_effect(NULL) {

    assert (src.get_effect != NULL);
    get_effect = src.get_effect;
  }

  void PowerUp::update() {

    is_alive = (pos.x + FRAME_RADIUS >= 0.0f);

    float delta_time = al_get_time() - time;

    rotation_angle += delta_time * POWERUP_VELOCITY / (PI * 8);
    mat3 translation = translate(delta_time * POWERUP_VELOCITY * dir);

    pos = translation * pos;

    time += delta_time;
  }

  void PowerUp::render() const {

    al_draw_rotated_bitmap(img, 25.0f, 25.0f, pos.x, pos.y, rotation_angle, 0);
  }
}