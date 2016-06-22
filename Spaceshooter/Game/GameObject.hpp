#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "../Math/vec3.hpp"

/*
	Base class used to derive all sprites within the game.
	It provides sprite position and move vector. 
*/

namespace sprites {

	class GameObject {

	public:

		GameObject(
			math::vec3 position,
			math::vec3 direction,
			bool alive = false);

		GameObject(const GameObject& src);

		virtual ~GameObject() {}

		virtual void update() {};
		
		/*
			Draws a rectangle where a sprite should be.
			Most derived classes  will override this function.
		*/
		virtual void render() const;

		const math::vec3& get_pos() const {
			return pos;
		}

		bool alive() const {
			return is_alive;
		}


		void set_alive(bool alive) {
			is_alive = alive;
		} 

	protected:

		bool is_alive;

		//	Coordinates
		math::vec3 pos;

		//	direction
		math::vec3 dir;
	};
}

#endif // BASE_HPP_INCLUDED
