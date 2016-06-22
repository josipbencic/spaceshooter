#include "GameLogicManager.hpp"

#include <cassert>

#include "../Core/Display.hpp"
#include "../Core/Audio.hpp"
#include "../Core/ResourceManager.hpp"
#include "../Core/SpriteMemoryPool.hpp"

#include "../Math/math2d.hpp"

#include "../Game/Spaceship.hpp"
#include "../Game/Comet.hpp"
#include "../Game/Explosion.hpp"
#include "../Game/Background.hpp"
#include "../Game/EnemySpaceship.hpp"
#include "../Game/PowerUp.hpp"
#include "../Game/Missile.hpp"

using namespace sprites;
using namespace math;
using namespace std;

#define SMP SpriteMemoryPool

namespace loop_tools {
	
	typedef GameLogicManager GLMAN;
	typedef BoringEnemySpaceship WES;
	typedef StrongEnemySpaceship SES;

	GLMAN::GameLogicManager(
		Display& display,
		Audio& audio,
		ResourceManager& res,
		Difficulty& difficulty,
		bool& health_bars) 
		: display(display)
		, audio(audio)
		, res(res)
		, bg(display, res)
		, weak_missiles()
		, strong_missiles()
		, comets()
		, explosions()
		, weak_enemies()
		, strong_enemies()
		, powerups()
		, ship(display, audio, res, weak_missiles, strong_missiles)
		, difficulty(difficulty)
		, health_bars(health_bars)
	{}

	void GLMAN::destroy_objects() {

		comets.clear();
		explosions.clear();
		strong_enemies.clear();
		weak_enemies.clear();
		powerups.clear();
		weak_missiles.clear();
		strong_missiles.clear();
	}

	GLMAN::~GameLogicManager() {

		destroy_objects();
	}

	template <typename Sprites>
	inline void render_container(const SMP<Sprites>& container) {

		for (typename SMP<Sprites>::const_iterator it = container.cbegin();
			it != container.cend(); ++it) 
			if ((*it).alive())
				(*it).render();
	}

	void GLMAN::render() const {
    
		bg.render();
		ship.render();
		if (health_bars) ship.render_hp_bars();

		render_container(comets);
		render_container(explosions);
		render_container(powerups);
		render_container(weak_missiles);
		render_container(strong_missiles);

		for (SMP<WES>::const_iterator it = weak_enemies.cbegin();
			it != weak_enemies.cend(); ++it)
			if ((*it).alive()) {

				(*it).render();

				if (health_bars)
					(*it).render_hp_bars();
			}
		
		for (SMP<SES>::const_iterator it = strong_enemies.cbegin();
			it != strong_enemies.cend(); ++it)
			if ((*it).alive()) {

				(*it).render();

				if (health_bars)
					(*it).render_hp_bars();
			}
	}

	void GLMAN::reset() {

		ship.reset();
		bg.reset_position();
		audio.play_background_music();
	}

	int GLMAN::update() {

		if (!ship.alive()) return -1;

		audio.play_background_music();

		ship.update();
		bg.update();

		update_objects();
		generate_game_objects();
		free_dead_objects();
		handle_collisions();

		return 0;
	}

	template <typename Sprites>
	inline void update_container(SMP<Sprites>& container) {

		for (typename SMP<Sprites>::iterator it = container.begin();
			it != container.end(); ++it)
			if ((*it).alive())
				(*it).update();
	}

	void GLMAN::update_objects() {

		update_container(weak_enemies);
		update_container(strong_enemies);
		update_container(comets);
		update_container(explosions);
		update_container(powerups);
		update_container(strong_missiles);
		update_container(weak_missiles);
	}

	template <typename Missile_>
	inline void missile_comet_collision(
		SMP<Missile_>& missiles,
		SMP<Comet>& comets,
		SMP<Explosion>& explosions,
		Spaceship& ship,
		Difficulty& difficulty,
		ResourceManager& res,
		Audio& audio) {

		for (typename SMP<Missile_>::iterator it = missiles.begin();
			it != missiles.end(); ++it) {
			if (!(*it).alive()) continue;

			for (typename SMP<Comet>::iterator it2 = comets.begin();
				it2 != comets.end(); ++it2)
				if ((*it2).alive() && circle_rect(
						(*it).get_pos(),
						(*it).radius(),
						(*it2).AABB_min(),
						(*it2).AABB_max())) {

					(*it2).set_alive(false);
					(*it).set_alive(false);
					ship.add_score((*it2).score() * static_cast<int>(difficulty) / 2);

					explosions.insert(Explosion(
						(*it).get_pos(), res.get_explosion(), audio));
				}
		}
	}

	template <typename Missile_, typename Enemy_>
	inline void missile_enemy_collision(
		SMP<Missile_>& missiles,
		SMP<Enemy_>& enemies,
		SMP<Explosion>& explosions,
		Spaceship& ship,
		Difficulty& difficulty,
		ResourceManager& res,
		Audio& audio) {

		for (typename SMP<Missile_>::iterator it = missiles.begin();
			it != missiles.end(); ++it) {
			if (!(*it).alive()) continue;

			for (typename SMP<Enemy_>::iterator it2 = enemies.begin();
				it2 != enemies.end(); ++it2)
				if ((*it2).alive() && circle_rect(
					(*it).get_pos(),
					(*it).radius(),
					(*it2).AABB_min(),
					(*it2).AABB_max())) {

					(*it2).take_damage((*it).damage());
					(*it).set_alive(false);
					ship.add_score((*it2).score() * static_cast<int>(difficulty) / 2);

					if (!(*it2).alive())
						explosions.insert(Explosion(
							(*it2).get_pos(), res.get_explosion(), audio));
				
				}
		}
	}

	template <typename Enemy_>
	inline void comet_enemy_collision(
		SMP<Comet>& comets,
		SMP<Enemy_>& enemies,
		SMP<Explosion>& explosions,
		ResourceManager& res,
		Audio& audio) {

		for (SMP<Comet>::iterator it = comets.begin();
			it != comets.end(); ++it) {
			if (!(*it).alive()) continue;

			for (typename SMP<Enemy_>::iterator it2 = enemies.begin();
				it2 != enemies.end(); ++it2)
				if ((*it2).alive() && rect_rect(
					(*it).AABB_min(), (*it).AABB_max(),
					(*it2).AABB_min(), (*it2).AABB_max())) {

 					(*it2).take_damage((*it).damage());
					(*it).set_alive(false);

					explosions.insert(Explosion(
						(*it).get_pos(), res.get_explosion(), audio));
				}		
		}
	}

	template <typename Missile_>
	inline void ship_missiles_collision(
		Spaceship& ship,
		SMP<Missile_>& missiles,
		Difficulty& difficulty) {

		for (typename SMP<Missile_>::iterator it = missiles.begin();
			it != missiles.end(); ++it)
			if ((*it).alive() && circle_rect(
					(*it).get_pos(),
					(*it).radius(),
					ship.AABB_min(),
					ship.AABB_max())) {
			
				ship.take_damage((*it).damage() * static_cast<int>(difficulty) / 2);
				(*it).set_alive(false);
			}
	}

	void GLMAN::handle_collisions() {

		ship_missiles_collision(ship, weak_missiles, difficulty);
		ship_missiles_collision(ship, strong_missiles, difficulty);

		for (SMP<Comet>::iterator it = comets.begin();
			it != comets.end(); ++it)
			if ((*it).alive() && rect_rect(
				ship.AABB_min(), ship.AABB_max(),
				(*it).AABB_min(), (*it).AABB_max())) {

					ship.take_damage((*it).damage() * static_cast<int>(difficulty) / 2);
					(*it).set_alive(false);
					explosions.insert(Explosion(
						(*it).get_pos(), res.get_explosion(), audio));
			}

		for (SMP<PowerUp>::iterator it = powerups.begin();
			it != powerups.end(); ++it) 
			if ((*it).alive() && circle_circle(
				ship.get_pos(), ship.get_bound_circle_radius(),
				(*it).get_pos(), PowerUp::FRAME_RADIUS)) {

				(*it).set_alive(false);
				(*it).get_effect(ship);
				audio.play_power_up();
			}

		comet_enemy_collision(comets, weak_enemies,
			explosions, res, audio);
		comet_enemy_collision(comets, strong_enemies,
			explosions, res, audio);
		
		missile_comet_collision(weak_missiles, comets,
			explosions, ship, difficulty, res, audio);

		missile_comet_collision(strong_missiles, comets,
			explosions, ship, difficulty, res, audio);

		missile_enemy_collision(weak_missiles, weak_enemies,
			explosions, ship, difficulty, res, audio);

		missile_enemy_collision(weak_missiles, strong_enemies,
			explosions, ship, difficulty, res, audio);

		missile_enemy_collision(strong_missiles, weak_enemies,
			explosions, ship, difficulty, res, audio);

		missile_enemy_collision(strong_missiles, strong_enemies,
			explosions, ship, difficulty, res, audio);
	}

	template<typename Sprite>
	void remove_dead(SMP<Sprite>& container) {

		for (typename SMP<Sprite>::iterator it = container.begin();
			it != container.end();)
			if (!(*it).alive())
				it = container.remove(it);
			else ++it;
	}

	void GLMAN::free_dead_objects() {
		
		remove_dead(weak_enemies);
		remove_dead(strong_enemies);
		remove_dead(comets);
		remove_dead(powerups);
	}


	struct SeedRand {
		SeedRand() { srand(time(0)); }
	};

	inline vec3 get_position(const Display& d) {

		float x = d.get_width() + 10.0f;
		float number = static_cast<float>(rand() % 16000 + 1);
		float y = remap(number, 1.0f, 16000.0f, 0.1f, 0.9f);
		y *= d.get_height();
		return point(x,y);
	}

	inline double chaos_formula(
		short comets, short weakones, short strongones, short missile,
		short weak_missile_num, short strong_missile_num);

	inline double win_lose_formula(
		short weakones, short strongones, double powerup_time,
		short missile, short health, short score);

	void GLMAN::generate_game_objects() {

		static SeedRand seed;
		static double last_boring_spawned = al_get_time();
		static double last_missile_powerup = al_get_time();
		static double last_comet = al_get_time();
		double time = al_get_time();

		int random_number = rand() % 8888;

		if (time - last_comet > 0.5 &&
			is_between(random_number, 150, 200)) {
		
			last_comet = time;
			comets.insert(
				Comet(get_position(display), res.get_comet(), display));
		}

		if (is_between(random_number, 25, 27))
			powerups.insert(PowerUp(display, get_position(display),
				res.get_health_power_up(), sprites::get_health_powerup));
					
		if (time - last_missile_powerup > 10.0 &&
			is_between(random_number, 28, 30)) {
		
			last_missile_powerup = time;
			powerups.insert(PowerUp(display, get_position(display),
				res.get_double_hit_power_up(), sprites::get_double_powerup));
		
		}

		if (time - last_missile_powerup > 10.0 &&
			is_between(random_number, 31, 33)) {

			last_missile_powerup = time;
			powerups.insert(PowerUp(display, get_position(display),
				res.get_strong_green_power_up(), sprites::get_strong_powerup));
		}

		if (time - last_boring_spawned > 3.0 &&
			is_between(random_number, 1183, 1197)) {
		
			last_boring_spawned = time;
			weak_enemies.insert(BoringEnemySpaceship(get_position(display),
				display, ship, weak_missiles, res.get_green_enemy_ship()));
		}

		if (is_between(random_number, 5032, 5039) &&
			StrongEnemySpaceship::free_sectors()) {

				strong_enemies.insert(StrongEnemySpaceship(get_position(display),
					display, ship, strong_missiles, res.get_green_enemy_ship(),
					res.get_strong_missile_reversed()));
			}
	}

}

#undef SMP
