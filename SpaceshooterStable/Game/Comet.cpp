#include "Comet.hpp"

#include "../Core/Display.hpp"

using namespace loop_tools;
using namespace math;

namespace sprites {

    Comet::Comet(	
		vec3 pos,
		ALLEGRO_BITMAP* img, 
		const Display& display)
		: GameObject( pos, vec3(-1.0f, 0.0f, 0.0f), true)
        , translation(translate(dir))
		, time(al_get_time())
		, current_frame(0)
		, frame_count(0.0)
		, frame_delay(0.01667)
		, img(img)
		, BOUND(42.0f)
		, FRAME_HEIGHT(96.0f)
		, FRAME_WIDTH(96.0f)
	{}

    void Comet::update() {

		is_alive = ( pos.x >= 0 );

		double delta_time = al_get_time() - time;
	
		translation = translate(
			static_cast<float>(delta_time)* COMET_VELOCITY * dir);
		pos = translation * pos;

		frame_count += delta_time;
        if (  frame_count >= frame_delay ) {
			current_frame = (current_frame - 1 + MAX_FRAME) % MAX_FRAME;
            frame_count -= frame_delay;
        }

		time += delta_time;
    }

    void Comet::render() const {

        float frame_x = (current_frame % ANIMATION_COLUMNS) * FRAME_WIDTH;
        float frame_y = (current_frame / ANIMATION_COLUMNS) * FRAME_HEIGHT;

        al_draw_bitmap_region(
			img, frame_x, frame_y, FRAME_WIDTH, FRAME_HEIGHT,
            pos.x - FRAME_WIDTH/2, pos.y - FRAME_HEIGHT/2, 0);
    }
}
