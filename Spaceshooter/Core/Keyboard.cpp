#include "Keyboard.hpp"

#include "../Core/Audio.hpp"

#include "../Game/Spaceship.hpp"
#include "../Game/HeadsUpDisplay.hpp"

#include "../Math/vec3.hpp"

#include <cstring>
#include <iostream>
#include <algorithm>


using namespace std;
using namespace sprites;
using namespace math;

namespace loop_tools {

  Keyboard::Keyboard() {
    memset(&state, 0, sizeof state);
  }

  Action Keyboard::update() {
    al_get_keyboard_state(&state);
    return input();
  }

  Action InterfaceKeyboard::input() {

    Action ret = Action::NOTHING;

    if (!al_key_down(&state, ALLEGRO_KEY_ESCAPE)
      && last_pressed[Action::ESCAPE]) 
      ret = Action::ESCAPE;

    if (!al_key_down(&state, ALLEGRO_KEY_ENTER)
      && last_pressed[Action::ENTER]) 
      ret =  Action::ENTER;

    if (!al_key_down(&state, ALLEGRO_KEY_UP)
      && last_pressed[Action::UP]) 
      ret =  Action::UP;

    if (!al_key_down(&state, ALLEGRO_KEY_DOWN) 
      && last_pressed[Action::DOWN])
      ret =  Action::DOWN;

    last_pressed[Action::DOWN] = al_key_down(&state, ALLEGRO_KEY_DOWN);
    last_pressed[Action::UP] = al_key_down(&state, ALLEGRO_KEY_UP);
    last_pressed[Action::ENTER] = al_key_down(&state, ALLEGRO_KEY_ENTER);
    last_pressed[Action::ESCAPE] = al_key_down(&state, ALLEGRO_KEY_ESCAPE);

    return ret;
  }

  Action PlayingKeyboard::input() {
    static bool escape_was_pressed = false;

    // change this escape
    if (!al_key_down(&state, ALLEGRO_KEY_ESCAPE)
      && escape_was_pressed) {
      escape_was_pressed = false;
      return Action::ESCAPE;
    }

    escape_was_pressed = al_key_down(&state, ALLEGRO_KEY_ESCAPE);


    if (al_key_down(&state, ALLEGRO_KEY_SPACE)) 
      ship.shoot();

    ship.dir = vector(0.0f, 0.0f) + 
      al_key_down(&state, ALLEGRO_KEY_UP) * vector(0.0f, -1.0f) + 
      al_key_down(&state, ALLEGRO_KEY_DOWN) * vector(0.0f, 1.0f) + 
      al_key_down(&state, ALLEGRO_KEY_LEFT) * vector(-1.0f, 0.0f) +
      al_key_down(&state, ALLEGRO_KEY_RIGHT) * vector(1.0f, 0.0f);

    if (ship.dir != vec3()) {
      ship.dir.normalize();
    }

    return Action::NOTHING;
  }
}
