#ifndef EXPLOSION_HPP_INCLUDED
#define EXPLOSION_HPP_INCLUDED

#include "../Game/GameObject.hpp"
#include "../Game/GameConstants.hpp"

#include <allegro5/allegro_image.h>

namespace loop_tools {
	class Audio;
}

namespace sprites {

	/*
		Uncollidable animation of explosion that will appear after destruction of every
		comet or enemy ship.
		
	*/
	class Explosion : public GameObject {
	public:
		/*
			Ctor
			- also plays an appropriate sound
		*/
		Explosion(	math::vec3 pos,
					ALLEGRO_BITMAP* bmp, 
					const loop_tools::Audio& audio);
		~Explosion();

		virtual void update(); 
		virtual void render() const;
 

	private:

		const float VELOCITY;

		double		time;
		double		frame_count;
		int			current_frame;

		ALLEGRO_BITMAP*		bitmap;

		static const int	MAX_FRAME = 31;
		static const int	FRAME_WIDTH = 128;
		static const int	FRAME_HEIGHT = 128;
		static const int	ANIMATION_COLUMNS = 8;
	};
}


#endif // EXPLOSION_HPP_INCLUDED
