#include "Spaceship.hpp"

#include "../Math/math2d.hpp"

#include "../Core/Display.hpp"
#include "../Core/Audio.hpp"
#include "../Core/ResourceManager.hpp"
#include "../Core/SpriteMemoryPool.hpp"

#include "../Game/GameConstants.hpp"
#include "../Game/Missile.hpp"

#include <allegro5/allegro_primitives.h>

using namespace math;
using namespace loop_tools;

namespace sprites {

  Spaceship::Spaceship(
    const Display&      display,
    const Audio&      audio,
    const ResourceManager&  res,
    SpriteMemoryPool<Missile>&    weak_missiles,
    SpriteMemoryPool<StrongMissile>&  strong_missiles)
    : GameObject(
      point(SHIP_STARTING_POS_X, SHIP_STARTING_POS_Y),
      math::vector(0.0f, 0.0f), true)
    , audio(audio)
    , display(display)
    , weak_missiles(weak_missiles)
    , strong_missiles(strong_missiles)
    , missile_type_(MissileType::NORMAL)
    , health(SHIP_MAX_HEALTH)
    , score(0)
    , time(al_get_time())
    , shoot_time(0.0)
    , power_up_time(0.0)
    , translation()
    , rotation(1.0f)
    , cur_frame(0)
    , animation_row(1)
    , bitmap(res.get_ship())
    , missile_bitmap(res.get_strong_missile())
    , RANGE(0.4 * display.get_width())
    , BOUND_X(24.0f)
    , BOUND_Y(24.0f)
  {}

  void Spaceship::out_of_screen() {
    if ( pos.x < 0 ) pos.x = 0;
    else if ( pos.x > RANGE ) pos.x = RANGE;

    if ( pos.y < 0 ) pos.y = 0;
    else if ( pos.y > display.get_height() ) pos.y = display.get_height();
  }

  void Spaceship::update() {
    is_alive = ( health > 0 );

    double delta_time = al_get_time() - time;

    power_up_time = math::max(power_up_time - delta_time, math::EPSILON);
    missile_type_ = power_up_time > math::EPSILON ? missile_type_ : MissileType::NORMAL;

    out_of_screen();
    calculate_animation();

    translation = translate(
      static_cast<float>(delta_time) * SHIP_VELOCITY * dir);

    pos = translation * pos;

    dir = vec3();

    time += delta_time;
  }

  void Spaceship::render() const {
    int frame_x = ( cur_frame % ANIMATION_COLUMNS) * FRAME_WIDTH;
    int frame_y = animation_row * FRAME_HEIGHT;
    al_draw_bitmap_region( bitmap, frame_x, frame_y, FRAME_WIDTH,
      FRAME_HEIGHT, pos.x - FRAME_WIDTH/2, pos.y - FRAME_HEIGHT/2, 0);
  }

  void Spaceship::render_hp_bars() const {
    //  hit points
    for(int i = 0; i < 10 * health / SHIP_MAX_HEALTH; ++i)
      al_draw_filled_rectangle(pos.x + (i-3) * 5, pos.y - FRAME_HEIGHT/2 - 5,
        pos.x + (i-2) *5, pos.y - FRAME_HEIGHT/2 -12, al_map_rgb(200,200,200));

    //  special ammo
    for(int i = 0; i < static_cast<int>(power_up_time); ++i)
      al_draw_filled_rectangle(pos.x +(i-3)*5, pos.y - FRAME_HEIGHT/2 - 10,
        pos.x + (i-2)*5, pos.y - FRAME_HEIGHT/2-15, al_map_rgb(150, 150, 220));
  }

  void Spaceship::shoot() {
    if (time - shoot_time < SHIP_MIN_SHOOT_INTERVAL) {
      return;
    }

    audio.play_missile_launch();

    switch (missile_type_) {
      case MissileType::NORMAL :
        weak_missiles.insert(Missile(
          pos + math::vector(35.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), display));
        break;

      case MissileType::DOUBLE :
        weak_missiles.insert(Missile(
          pos + math::vector(35.0f, 5.0f), vec3(1.0f, 0.0f, 0.0f), display));
        weak_missiles.insert(Missile(
          pos + math::vector(35.0f, -5.0f), vec3(1.0f, 0.0f, 0.0f), display));
        break;

      case MissileType::STRONG_GREEN :
        strong_missiles.insert(StrongMissile(
          pos + math::vector(35.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f),
            display, missile_bitmap));
        break;
    }

    shoot_time = time;
  }

  void Spaceship::reset() {
    is_alive = true;
    health = SHIP_MAX_HEALTH;
    score = 0;
    pos.x = SHIP_STARTING_POS_X;
    pos.y = SHIP_STARTING_POS_Y;
    dir = vec3();
    animation_row = 1;
    cur_frame = 0;
    missile_type_ = MissileType::NORMAL;
    power_up_time = 0.0;
    time = al_get_time();
  }

  void Spaceship::calculate_animation() {
    if (dir.y < 0.0f)       animation_row = 0;
    else if (dir.y > 0.0f)  animation_row = 2;
    else                    animation_row = 1;

    if (dir.x < 0.0f)       cur_frame = 2;
    else if (dir.x > 0.0f)  cur_frame = 1;
    else                    cur_frame = 0;
  }
}
