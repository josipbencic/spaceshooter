#ifndef BITMAP_MANAGER_INCLUDED
#define BITMAP_MANAGER_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

namespace loop_tools {

	/*
		Object that will take care of bitmap and font resources.
		Ctor will load and Dtor will destroy all bitmaps.
	*/
	class ResourceManager {
	private:
		typedef ALLEGRO_BITMAP* p_bmp;
		typedef ALLEGRO_FONT* p_font;
	public:
		ResourceManager();
		~ResourceManager();	
		
		p_bmp	get_ship() const					{ return p_ship; }
		p_bmp	get_comet() const					{ return p_comet; }
		p_bmp	get_explosion() const				{ return p_explosion; }
		p_bmp	get_green_enemy_ship() const		{ return p_green_enemy_ship; }
		p_bmp	get_health_power_up() const			{ return p_health_power_up; }
		p_bmp	get_double_hit_power_up() const		{ return p_double_hit_power_up; }
		p_bmp	get_strong_green_power_up() const	{ return p_strong_green_power_up; }
		p_bmp	get_strong_missile_reversed() const { return p_strong_missile_reversed; }
		p_bmp	get_strong_missile() const			{ return p_strong_missile; }
		p_bmp	get_foreground() const				{ return p_foreground; }
		p_bmp	get_middleground() const			{ return p_middleground; }
		p_bmp	get_background() const				{ return p_background; }

		p_font	get_font18() const					{ return p_font18; }
		p_font	get_font36() const					{ return p_font36; }
		p_font	get_font67() const					{ return p_font67; }

	private:
		p_bmp p_ship;
		p_bmp p_comet;
		p_bmp p_explosion;
		p_bmp p_green_enemy_ship;
		p_bmp p_health_power_up;
		p_bmp p_double_hit_power_up;
		p_bmp p_strong_missile_reversed;
		p_bmp p_strong_missile;
		p_bmp p_strong_green_power_up;
		p_bmp p_foreground;
		p_bmp p_middleground;
		p_bmp p_background;

		p_font p_font18;
		p_font p_font36;
		p_font p_font67;

		/*
			No copying/assigning.
		*/
		ResourceManager(const ResourceManager&);
		const ResourceManager& operator= (const ResourceManager&);
	};
}


#endif 