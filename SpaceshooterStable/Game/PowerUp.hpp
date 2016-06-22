#ifndef POWER_UP_HPP_INCLUDED
#define POWER_UP_HPP_INCLUDED

#include "../Game/GameObject.hpp"

namespace loop_tools {
	class Display;
}

namespace sprites {

	class Spaceship;

	void get_health_powerup(Spaceship& ship);
	void get_double_powerup(Spaceship& ship);
	void get_strong_powerup(Spaceship& ship);

	class PowerUp : public GameObject {
	public:
		PowerUp(
			const loop_tools::Display& display, 
			math::vec3 pos,
			ALLEGRO_BITMAP* img,
			void (*get_effect_func)(Spaceship&));

		PowerUp(const PowerUp& src);
		
		virtual ~PowerUp() {}

		virtual void	update();
		virtual void	render() const;

		void	(*get_effect)(Spaceship& ship);

		static const float	FRAME_RADIUS;

	protected:
		static const int	FRAME_DELAY = 10;
		double				time;
		double				frame_count;
		float				rotation_angle;
		ALLEGRO_BITMAP*		img;
	};
}

#endif