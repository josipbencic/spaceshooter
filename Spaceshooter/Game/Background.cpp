#include "Background.hpp"

#include "../Core/Display.hpp"
#include "../Core/ResourceManager.hpp"

using namespace loop_tools;
using namespace math;

namespace sprites {

	const float Background::FRAME_WIDTH[] = {800, 4000, 800};

	Background::Background(
		const Display& display,
		const ResourceManager& res) 
		: display(display)
		, dir(-1.0f, 0.0f, 0.0f) {

		bitmap[0] = res.get_foreground();
		bitmap[1] = res.get_middleground();
		bitmap[2] = res.get_background();

		for (unsigned i = 0; i < 3; i++) {
			pos[i] = vec3(0.0f, 0.0f, 1.0f);
			pos[i+3] = vec3(FRAME_WIDTH[i], 0.0f, 1.0f);
		}
	}

	void Background::update() {

		static float last_time = al_get_time();
		float delta_time = al_get_time() - last_time;

		for (unsigned i = 0; i < 3; i++)
			translation[i] = translate(delta_time * BACKGROUND_VELOCITY[i] * dir);

		for (unsigned i = 0; i < 6; i++) 
			pos[i] = translation[i % 3] * pos[i];

		for (unsigned i = 0; i < 6; i++) 
			if (pos[i].x + FRAME_WIDTH[i % 3] < 0.0f) 
				pos[i].x += 2 * FRAME_WIDTH[i % 3];

		last_time += delta_time;
    }

	void Background::reset_position() {
		
	
		for (unsigned i = 0; i < 3; i++)
			pos[i].x = 0.0f;

		for (unsigned i = 3; i < 6; i++)
			pos[i].x = FRAME_WIDTH[i%3];
	}

    void Background::render() const {

		al_clear_to_color(al_map_rgb(5,5,5));

		for (int i = 5; i > -1; i--)
			al_draw_bitmap(bitmap[i%3], pos[i].x, pos[i].y, 0);
    }
}


