#include "Explosion.hpp"

#include "../Core/Audio.hpp"
#include "../Math/math2d.hpp"

#include <allegro5/allegro_acodec.h>

using namespace std;
using namespace loop_tools;
using namespace math;


namespace sprites {

  Explosion::Explosion(
    vec3 pos,
    ALLEGRO_BITMAP* bmp,
    const Audio& audio)
    : GameObject(pos, vec3(-1.0f, 0.0f, 1.0f).normalize(), true)
    , VELOCITY(3.0f)
    , time(al_get_time())
    , frame_count(0.0)
    , current_frame(0)
    , bitmap(bmp) {
    audio.play_explosion();
  }

  Explosion::~Explosion() {}

    void Explosion::update() {
    double delta_time = al_get_time() - time;

    mat3 translation = translate(delta_time * VELOCITY * dir);
    pos = translation * pos;

    is_alive = (pos.x + FRAME_WIDTH) >= 0 &&
      current_frame <= MAX_FRAME;

    frame_count += delta_time;
    if (EXPLOSION_FRAME_DELAY - frame_count < EPSILON) {
      ++current_frame;
      frame_count = 0;
    }

    time += delta_time;
  }

  void Explosion::render() const {

    float frame_x = ( current_frame % ANIMATION_COLUMNS ) * FRAME_WIDTH;
    float frame_y = ( current_frame / ANIMATION_COLUMNS ) * FRAME_HEIGHT;

    al_draw_bitmap_region(bitmap, frame_x, frame_y, FRAME_WIDTH, FRAME_HEIGHT,
      pos.x - FRAME_WIDTH/2, pos.y - FRAME_HEIGHT/2, 0);
  }
}


