#include "EnemySpaceship.hpp"


#include "../Core/Display.hpp"
#include "../Math/math2d.hpp"
#include "../Game/Missile.hpp"
#include "../Game/Spaceship.hpp"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace loop_tools;
using namespace std;
using namespace math;


namespace sprites {

	EnemySpaceship::EnemySpaceship(
		const vec3		pos,
		const Display&	display,
		Spaceship&		ship,
		ALLEGRO_BITMAP*	img)
		: GameObject(pos, vector(-1.0f, 0.0f), true)
		, display(display)
		, ship(ship)
		, BOUND(24.0f)
		, time(al_get_time())
		, last_shot(al_get_time())
		, health(ENEMY_MAX_HEALTH)
		, current_frame(1)
		, animation_row(2)
		, img(img)
	{}

	EnemySpaceship::EnemySpaceship(const EnemySpaceship& src)
		: GameObject(src)
		, display(src.display)
		, ship(src.ship)
		, BOUND(24.0f)
		, time(al_get_time())
		, last_shot(al_get_time())
		, health(src.health)
		, current_frame(src.current_frame)
		, animation_row(src.animation_row)
		, img(src.img)
	{}

	EnemySpaceship::~EnemySpaceship() {}

	void EnemySpaceship::render() const {

		int frame_x = (current_frame % ANIMATION_COLUMNS) * FRAME_WIDTH;
		int frame_y = animation_row * FRAME_HEIGHT;

		al_draw_bitmap_region(img, frame_x, frame_y, FRAME_WIDTH,
			FRAME_HEIGHT, pos.x - FRAME_WIDTH/2, pos.y - FRAME_WIDTH/2, 0);
	}

	void EnemySpaceship::render_hp_bars() const {
		
		static ALLEGRO_COLOR color1 = al_map_rgb(52, 201, 52);
		static ALLEGRO_COLOR color2 = al_map_rgb(220, 220, 220);

		al_draw_filled_rectangle(
			pos.x - ENEMY_MAX_HEALTH / 2,
			pos.y - 26,
			pos.x + ENEMY_MAX_HEALTH / 2,
			pos.y - 32,
			color2);

		al_draw_filled_rectangle(
			pos.x - ENEMY_MAX_HEALTH / 2,
			pos.y - 27,
			pos.x - ENEMY_MAX_HEALTH / 2 + health,
			pos.y - 31,
			color1);
	}

	//========================================================================
	//	BORING SHIP

	typedef BoringEnemySpaceship B;

	B::BoringEnemySpaceship(
		const vec3					pos,
		const Display&				display,
		Spaceship&					ship,
		SpriteMemoryPool<Missile>&	missiles,
		ALLEGRO_BITMAP*				img)
		: EnemySpaceship(
			pos, display, ship, img)
		, missiles(missiles)
		, translation() {

		current_frame = 2;
		animation_row = 1;
	}

	B::BoringEnemySpaceship(const B& src)
		: EnemySpaceship(src)
		, missiles(src.missiles)
		, translation(src.translation)
	{}

	B::~BoringEnemySpaceship() {}

	void B::move() {

		double delta_time = al_get_time() - time;

		translation = translate(BORING_ENEMY_VELOCITY * delta_time * dir);

		pos = translation * pos;

		time += delta_time;
	}
	
	void B::shoot() {

		if (time - last_shot < BORING_ENEMY_SHOOT_INTERVAL)
			return;
		last_shot = time;

		missiles.insert(Missile(pos + vector(-50.0f, 0.0f), dir, display));
	}

	void B::update() {

		is_alive = pos.x >= 0.0f && health > 0;

		shoot();
		move();
	}

	//=======================================================================
	//	STRONG SHIP
	
	/*
		Display is separated in 12 sections (4 x 3)
		Each strong ship chooses its section, and moves there over time.
	*/
	bool StrongEnemySpaceship::taken_sectors[12] = {0};
	short StrongEnemySpaceship::next_sector = 7;

	bool StrongEnemySpaceship::free_sectors() {

		for (unsigned i = 0; i < 4; i++) {
			bool flag = true;
			for (unsigned j = 0; j < 3; j++)
				if (StrongEnemySpaceship::taken_sectors[i * 3 + j]) {
					flag = false;
					break;
				}

			if (flag) {
				StrongEnemySpaceship::next_sector = i * 3 + rand() % 3;
				return true;
			}
		}
		return false;
	}

	vec3 get_final_position(const Display& d, short sector) {

		float sector_x = static_cast<float>(sector % 3);
		float sector_y = static_cast<float>(sector / 3);

		/*
			Choose a point inside the sector.
		*/
		float x = static_cast<float>(rand() % 16000);
		float y = static_cast<float>(rand() % 30000);


		x = remap(x, 0.0f, 15999.0f,
			(sector_x + 6.0f) * d.get_width() /12, (sector_x + 9.0f) * d.get_width() / 12);
		y = remap(y, 0.0f, 29999.0f,
			(sector_y * 2 + 1.0f) * d.get_height()/9, (sector_y * 2 + 2.0f) * d.get_height()/9);

		return point(x, y);
	}


	StrongEnemySpaceship::StrongEnemySpaceship(
		const vec3							starting_position,
		const Display&						display,
		Spaceship&							ship,
		SpriteMemoryPool<StrongMissile>&	missiles,
		ALLEGRO_BITMAP*						img,
		ALLEGRO_BITMAP*						missile_img)
		: EnemySpaceship(starting_position, display, ship, img)
		, missiles(missiles)
		, sector(next_sector)
		, starting_position(starting_position)
		, final_position(get_final_position(display, next_sector))
		, lerp_factor(0.0f)
		, missile_img(missile_img) {
		
		StrongEnemySpaceship::taken_sectors[sector] = true;
	}

	StrongEnemySpaceship::StrongEnemySpaceship(
		const StrongEnemySpaceship& src)
		: EnemySpaceship(src)
		, missiles(src.missiles)
		, sector(src.sector)
		, starting_position(src.starting_position)
		, final_position(src.final_position)
		, lerp_factor(src.lerp_factor)
		, missile_img(src.missile_img) {

		StrongEnemySpaceship::taken_sectors[sector] = true;
	}

	StrongEnemySpaceship::~StrongEnemySpaceship() {
		
		taken_sectors[sector] = false;
	}

	void StrongEnemySpaceship::move() {

		float delta_time = static_cast<float>(al_get_time() - time);
		lerp_factor += delta_time / 3;

		pos = lerp(
			starting_position,
			final_position,
			clamp_to_01(lerp_factor));

		time += delta_time;
	}

	inline bool ship_in_line(
		const Display& d, const Spaceship& ship, const vec3 pos) {

			return	abs(ship.get_pos().y - pos.y) < 0.1f * d.get_height();
	}

	void StrongEnemySpaceship::update() {

		/*

			This line is very important.
			when expanding SMP, all copy-ctors are called BEFORE
			dtors, and it clears the taken_sectors.
		*/
		StrongEnemySpaceship::taken_sectors[sector] = true;

		is_alive = pos.x >= 0 && health > 0;

		if (ship_in_line(display, ship, pos))
			shoot();

		float tmp_y = pos.y;
		move();

		//	update animation
		if ( pos.y - tmp_y > 0.5f )
			animation_row = 2;
		else if ( pos.y - tmp_y < -0.5f)
			animation_row = 0;
		else animation_row = 1;

		current_frame = lerp_factor < 1.0f ? 1 : 2;
	}

	void StrongEnemySpaceship::shoot() {
		
		if (time - last_shot < STRONG_ENEMY_SHOOT_INTERVAL)
			return;

		last_shot = time;

		missiles.insert(StrongMissile(
			pos + vector(-50.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), display, missile_img));
	}
}
