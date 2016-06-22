#ifndef GAME_CONSTANTS_HPP
#define GAME_CONSTANTS_HPP


namespace sprites {

	/*
		Player can send a missile every MIN_SHOOT_INTERVAL seconds
	*/
	extern const double	SHIP_MIN_SHOOT_INTERVAL;
	extern const int	SHIP_MAX_HEALTH;
	extern const float	SHIP_STARTING_POS_X;
	extern const float	SHIP_STARTING_POS_Y;
	extern const float	SHIP_VELOCITY;

	/*
		Missile specifications.
	*/
	extern const int	MISSILE_DAMAGE_NORMAL;
	extern const int	MISSILE_DAMAGE_STRONG;
	extern const float	MISSILE_VELOCITY;

	/*
		
	*/
	extern const float	BACKGROUND_VELOCITY[3];

	/*
		Defines how long explosions are going to stay
		in the screen.
	*/
	extern const double EXPLOSION_FRAME_DELAY;

	/*
		Powerup specifications.
	*/
	extern const float	POWERUP_VELOCITY;
	extern const int	POWERUP_HEALTH_AMOUNT;
	extern const double	POWERUP_DOUBLE_DURATION;
	extern const double	POWERUP_STRONG_DURATION;

	/*
		Comet damage infliction,
		score value and velocity.
	*/
	extern const int	COMET_DAMAGE;
	extern const int	COMET_SCORE;
	extern const float	COMET_VELOCITY;

	/*
		Enemy specifications.
	*/
	extern const int	ENEMY_MAX_HEALTH;

	extern const int	BORING_ENEMY_SCORE;
	extern const double	BORING_ENEMY_SHOOT_INTERVAL;
	extern const float	BORING_ENEMY_VELOCITY;


	extern const int	STRONG_ENEMY_SCORE;
	extern const double	STRONG_ENEMY_SHOOT_INTERVAL;
}

#endif	// GAME_CONSTANTS_HPP
