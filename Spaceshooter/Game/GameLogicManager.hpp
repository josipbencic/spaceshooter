#ifndef GAMELOGICMANAGER_HPP
#define GAMELOGICMANAGER_HPP

#include "../Core/SpriteMemoryPool.hpp"

#include "../Game/Spaceship.hpp"
#include "../Game/Background.hpp"

namespace sprites {
	class Comet;
	class Explosion;
	class BoringEnemySpaceship;
	class StrongEnemySpaceship;
	class PowerUp;
	class Missile;
	class StrongMissile;
}

namespace loop_tools {

	class Display;
	class Audio;
	class ResourceManager;
	enum Difficulty;

	class GameLogicManager {
	public:
		GameLogicManager(
			Display& display,
			Audio& audio,
			ResourceManager& res,
			Difficulty& difficulty,
			bool& draw_health_bars);
		~GameLogicManager();

		sprites::Spaceship& get_ship() {
			return ship;
		}

		void	render() const;
		int		update();
		void	destroy_objects();
		void	reset();

	private:
		void update_objects();
		void handle_collisions();
		void free_dead_objects();
		void generate_game_objects();

		Display&				display;
		Audio&					audio;
		ResourceManager&		res;

		sprites::Background		bg;

		SpriteMemoryPool<sprites::Missile>				weak_missiles;
		SpriteMemoryPool<sprites::StrongMissile>		strong_missiles;

		SpriteMemoryPool<sprites::Comet>				comets;
		SpriteMemoryPool<sprites::Explosion>			explosions;

		SpriteMemoryPool<sprites::BoringEnemySpaceship> weak_enemies;
		SpriteMemoryPool<sprites::StrongEnemySpaceship> strong_enemies;

		SpriteMemoryPool<sprites::PowerUp>				powerups;


		sprites::Spaceship		ship;
		
		Difficulty& difficulty;

		//	draw HP bars?
		bool&	health_bars;
	};
}

#endif