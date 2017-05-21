#include "GameObject.hpp"

#include <allegro5/allegro_primitives.h>

#include "../Math/vec3.hpp"

using namespace std;
using namespace math;

namespace sprites {

  GameObject::GameObject(
    math::vec3 position,
    math::vec3 direction,
    bool alive)
    : is_alive(alive)
    , pos(position)
    , dir(direction)
    {}

  GameObject::GameObject(const GameObject& src)
    : is_alive(src.is_alive)
    , pos(src.pos)
    , dir(src.dir)
  {}

  void GameObject::render() const {

    static ALLEGRO_COLOR color = al_map_rgb(20, 100, 200);

    al_draw_filled_rectangle(pos.x + 15, pos.y - 15,
      pos.x + 15, pos.y + 15, color);
  }

}
