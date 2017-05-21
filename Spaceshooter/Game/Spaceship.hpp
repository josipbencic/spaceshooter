#ifndef SPACESHIP_HPP_INCLUDED
#define SPACESHIP_HPP_INCLUDED

#include "../Game/GameObject.hpp"
#include "../Game/GameConstants.hpp"

#include "../Math/math2d.hpp"

namespace sprites {
  class Missile;
  class StrongMissile;
  enum  MissileType;
  class Comet;
  class EnemySpaceship;
}

namespace loop_tools {
  class Display;
  class Audio;
  class PlayingKeyboard;
  class ResourceManager;
  template <typename Sprite> class SpriteMemoryPool;
}

namespace sprites {

  class Spaceship: public GameObject {

    friend class Comet;
    friend class ::loop_tools::PlayingKeyboard;

  public:

    Spaceship(
      const loop_tools::Display&                    display,
      const loop_tools::Audio&                      audio,
      const loop_tools::ResourceManager&            res,
      loop_tools::SpriteMemoryPool<Missile>&        weak_missiles,
      loop_tools::SpriteMemoryPool<StrongMissile>&  strong_missiles);

    virtual void  update();
    virtual void  render() const;
    void          render_hp_bars() const;

    void shoot();
    void reset();

    inline void add_score(int num = 1) {
      score += num;
    }

    inline void take_damage(int damage) {
      if ( health <= 0) return;
      health -= damage;
    }

    inline int get_score() const { return score; }
    inline int get_health() const { return health; }

    inline void set_health(int new_health) {
      health = math::min(SHIP_MAX_HEALTH, new_health);
    }

    inline void reset_power_up_timer(double duration) {
      power_up_time = duration;
    }

    inline void set_current_missile_type(MissileType type) {
      missile_type_ = type;
    }

    inline MissileType missile_type() const {
      return missile_type_;
    }

    inline math::vec3 AABB_min() const {
      return math::point(pos.x - BOUND_X, pos.y - BOUND_Y);
    }

    inline math::vec3 AABB_max() const {
      return math::point(pos.x + BOUND_X, pos.y + BOUND_Y);
    }

    inline float get_bound_circle_radius() const {
      return BOUND_X * math::ROOT_OF_2;
    }

    private:

    void out_of_screen();
    void calculate_animation();

    const loop_tools::Audio&      audio;
    const loop_tools::Display&      display;

    loop_tools::SpriteMemoryPool<Missile>&      weak_missiles;
    loop_tools::SpriteMemoryPool<StrongMissile>&  strong_missiles;
    MissileType                   missile_type_;

    int   health;
    int   score;

    double  time;
    double  shoot_time;
    double  power_up_time;

    /*
      Model matrix
    */
    math::mat3  translation;
    math::mat3  rotation;

    //  animation variables
      //  all bitmaps are stored in one big bitmap
      //  whose regions are rendered
    int   cur_frame;
    int   animation_row;

    //  bitmap pointer to pass for rendering
    ALLEGRO_BITMAP*   bitmap;
    ALLEGRO_BITMAP*   missile_bitmap;


    //  Spaceship cannot move beyond
    const float RANGE;

    //  collision variables
    const float BOUND_X;
    const float BOUND_Y;

    //  ANIMATIONS
    //  size of a single bitmap inside the big bitmap
    static const int  MAX_FRAME = 3;
    static const int  FRAME_WIDTH = 46;
    static const int  FRAME_HEIGHT = 41;
    static const int  ANIMATION_COLUMNS = 3;
  };
}

#endif // SPACESHIP_HPP_INCLUDED