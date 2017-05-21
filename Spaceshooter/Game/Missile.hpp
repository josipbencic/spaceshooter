#ifndef MISSLE_HPP_INCLUDED
#define MISSLE_HPP_INCLUDED

#include "../Game/GameObject.hpp"
#include "../Game/GameConstants.hpp"

#include "../Math/mat3.hpp"

namespace loop_tools {
  class Display;
}

namespace sprites {

  class Comet;

  enum MissileType {
    NORMAL,
    DOUBLE,
    STRONG_GREEN,
    STRONG_RED
  };

  class Missile : public GameObject {

  public:
    Missile(
      math::vec3 pos,
      math::vec3 dir,
      const loop_tools::Display& display);

    Missile(const Missile& rhs);

    const Missile& operator= (const Missile& rhs);

    virtual void update();
    virtual void render() const;

    virtual int damage() const {
      return MISSILE_DAMAGE_NORMAL;
    }

    virtual float radius() const {
      return 2.0f;
    }

  private:
    const loop_tools::Display&  display;
    double            time;

    math::mat3          translation;
    };

  class StrongMissile : public Missile {
    friend class StrongEnemySpaceship;

  public:
    StrongMissile(
      math::vec3 pos,
      math::vec3 dir,
      const loop_tools::Display& __display,
      ALLEGRO_BITMAP* bmp);

    StrongMissile(const StrongMissile& rhs);

    virtual ~StrongMissile();

    virtual void render() const;
    virtual int damage() const {
      return MISSILE_DAMAGE_STRONG;
    }
    virtual float radius() const {
      return MISSILE_HEIGHT;
    }

  private:
    static const float MISSILE_WIDTH;
    static const float MISSILE_HEIGHT;

    ALLEGRO_BITMAP* bmp;
  };

}


#endif // MISSLE_HPP_INCLUDED
