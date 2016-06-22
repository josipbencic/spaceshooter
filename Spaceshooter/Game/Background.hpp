#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <allegro5/allegro.h>

#include "../Math/vec3.hpp"
#include "../Math/mat3.hpp"

#include "../Game/GameConstants.hpp"

/*
	Background class handles 3 different backgrounds 
	that implement paralax scrolling technique to give a 3D-like impression.

	It also clears the screen after each frame.
*/

namespace loop_tools {
	class Display;
	class ResourceManager;
}

namespace sprites {

	class Background {
	public:
		/*
			Ctor
				- loads bitmaps used for background 
					- converts their masks to alpha channel where needed
				- asserts the given pointers.
		*/
		Background(
			const loop_tools::Display& display,
			const loop_tools::ResourceManager& res);

		void update();
		void render() const;
		void reset_position();

	private:

		/*
			Display is used to get height and width to render backgrounds 
			properly even if the resolution is changed during the runtime.
		*/
		const loop_tools::Display& display;
	
		enum {
			FOREGROUND = 0,
			MIDDLEGROUND = 1,
			BACKGROUND = 2,
			FOREGROUND2 = 3,
			MIDDLEGROUND2 = 4,
			BACKGROUND2 = 5
		};
		
		math::mat3 translation[3];
		math::vec3 pos[6];
		math::vec3 dir;

		/*
			Since the levels are infinite, bitmaps are redrawn.
		*/
		static const float FRAME_WIDTH[3];
		
		ALLEGRO_BITMAP* bitmap[3];

		//	won't be used for now
		Background(const Background&);
		const Background& operator= (const Background&);
	};
}

#endif // BACKGROUND_HPP
