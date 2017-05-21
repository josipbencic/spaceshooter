#ifndef ENEMYSPACESHIP_HPP_INCLUDED
#define ENEMYSPACESHIP_HPP_INCLUDED


#include "../Core/SpriteMemoryPool.hpp"

#include "../Math/mat3.hpp"

#include "../Game/GameObject.hpp"
#include "../Game/GameConstants.hpp"


namespace loop_tools {
  class Display;
}

namespace sprites {

  class Missile;
  class StrongMissile;
  class Spaceship;

  class EnemySpaceship : public GameObject {
  public:

    /*
      Currently, all enemy spaceships have the same bitmap.
    */
    EnemySpaceship(
      const math::vec3      pos,
      const loop_tools::Display&  display,
      Spaceship&          ship,
      ALLEGRO_BITMAP*       img);

    EnemySpaceship(const EnemySpaceship& src);

    virtual ~EnemySpaceship();

    virtual void  shoot() = 0;

    virtual void  render() const;
    void          render_hp_bars() const;
    virtual void  update() {}
    virtual void  move() = 0;
    virtual int   score() const = 0;

    inline math::vec3 AABB_min() const {
      return math::vec3(pos.x - BOUND, pos.y - BOUND, 1.0f);
    }

    inline math::vec3 AABB_max() const {
      return math::vec3(pos.x + BOUND, pos.y + BOUND, 1.0f);
    }

    inline void take_damage(unsigned damage = 1) {
      health -= damage;
      is_alive = health > 0;
    }

  protected:
    const loop_tools::Display&  display;
    Spaceship&          ship;

    const float     BOUND;
    double        time;
    double        last_shot;
    int         health;
    unsigned      current_frame;
    unsigned      animation_row;
    ALLEGRO_BITMAP*   img;

    static const int  FRAME_WIDTH = 43;
    static const int  FRAME_HEIGHT = 41;
    static const int  ANIMATION_COLUMNS = 3;
    static const int  MAX_FRAME = 3;
  };

  class BoringEnemySpaceship : public EnemySpaceship {
  public:
    BoringEnemySpaceship(
      const math::vec3            pos,
      const loop_tools::Display&        display,
      Spaceship&                ship,
      loop_tools::SpriteMemoryPool<Missile>&  missiles,
      ALLEGRO_BITMAP*             img);

    BoringEnemySpaceship(const BoringEnemySpaceship& src);

    virtual ~BoringEnemySpaceship();

    virtual void move();
    virtual void shoot();
    virtual void update();
    virtual int score() const {
      return BORING_ENEMY_SCORE;
    }

  private:
    loop_tools::SpriteMemoryPool<Missile>& missiles;

    math::mat3 translation;
  };

  class StrongEnemySpaceship :
    public EnemySpaceship {

  public:
    StrongEnemySpaceship(
      const math::vec3                starting_pos,
      const loop_tools::Display&            display,
      Spaceship&                    ship,
      loop_tools::SpriteMemoryPool<StrongMissile>&  missiles,
      ALLEGRO_BITMAP*                 img,
      ALLEGRO_BITMAP*                 missile_img);

    StrongEnemySpaceship(const StrongEnemySpaceship& src);

    virtual ~StrongEnemySpaceship();

    virtual void shoot();
    virtual void update();
    virtual void move();
    virtual int score() const {
      return STRONG_ENEMY_SCORE;
    }

    static bool   free_sectors();
    static short  next_sector;
    static bool   taken_sectors[12];

  private:

    loop_tools::SpriteMemoryPool<StrongMissile>& missiles;

    short             sector;
    math::vec3        starting_position;
    math::vec3        final_position;
    float             lerp_factor;

    ALLEGRO_BITMAP*   missile_img;
  };

}
#endif