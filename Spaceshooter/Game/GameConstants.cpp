#include "GameConstants.hpp"


namespace sprites {

	const double		SHIP_MIN_SHOOT_INTERVAL = 0.5;
	const int			SHIP_MAX_HEALTH = 200;
	const float			SHIP_STARTING_POS_X = 50.0f;
	const float			SHIP_STARTING_POS_Y = 300.0f;
	const float			SHIP_VELOCITY = 200.0f;

	const int			MISSILE_DAMAGE_NORMAL = 20;
	const int			MISSILE_DAMAGE_STRONG = 35;
	const float			MISSILE_VELOCITY = 700.0f;

	const float			BACKGROUND_VELOCITY[] = {100.0f, 50.0f, 30.0f};

	const double		EXPLOSION_FRAME_DELAY = 0.016667;

	const float			POWERUP_VELOCITY = 130.0f;
	const int			POWERUP_HEALTH_AMOUNT = 80;
	const double		POWERUP_DOUBLE_DURATION = 15.0;
	const double		POWERUP_STRONG_DURATION = 8.0;

	const int			COMET_DAMAGE = 15;
	const int			COMET_SCORE = 25;
	const float			COMET_VELOCITY = 300.0f;

	extern const int	ENEMY_MAX_HEALTH = 50;

	const int			BORING_ENEMY_SCORE = 35;
	const double		BORING_ENEMY_SHOOT_INTERVAL = 0.5;
	const float			BORING_ENEMY_VELOCITY = 85.0f;

	const int			STRONG_ENEMY_SCORE = 75;
	const double		STRONG_ENEMY_SHOOT_INTERVAL = 1.2;
}
