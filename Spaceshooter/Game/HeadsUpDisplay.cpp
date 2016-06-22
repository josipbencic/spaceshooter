#include "HeadsUpDisplay.hpp"

#include "../Core/Display.hpp"
#include "../Core/Audio.hpp"
#include "../Core/ResourceManager.hpp"

#include "../Game/Spaceship.hpp"

#include <cstdio>
#include <ctime>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace sprites;
using namespace std;

#define UI_COLOR_1 al_map_rgb(20, 70, 255)
#define UI_COLOR_2 al_map_rgb(200, 200, 200)
#define UI_COLOR_3 al_map_rgb(70, 70, 70)
#define UI_COLOR_4 al_map_rgb(10, 10, 10)

namespace loop_tools {

	HeadsUpDisplay::HeadsUpDisplay(
			Display& display,
			Audio& audio,
			ResourceManager& res)
			: display(display)
			, audio(audio)
			, res(res)
	{}

	PlayingHUD::PlayingHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res,
			Spaceship& ship)
			: HeadsUpDisplay(display, audio, res)
			, ship(ship)
	{}

	inline double frame_time() {

		static double time = al_get_time();
		static double last_update = 0.0;
		static double last_frame_time = 0.0;
		static double delta = 0.0;
		static int	frame_count = 0;

		delta += al_get_time() - time;
		time += delta;
		frame_count++;

		if (time - last_update > 1.0) {
			last_update = time;
			last_frame_time = delta / frame_count;
			delta = 0;
		}
		return last_frame_time;
	}

	void PlayingHUD::render() const {

		static const int point_pos = display.get_width() - 120;
		static const int health_pos = display.get_width() - 250;
		static const ALLEGRO_COLOR color =  UI_COLOR_1;
		double frame_length = frame_time();

		al_draw_textf(res.get_font18(), color, 5, 5, 0, "%lf ms", frame_length * 1000);
		al_draw_textf(res.get_font18(), color,
			point_pos, 5, 0, "%i points", ship.get_score());
		al_draw_textf(res.get_font18(), color,
			health_pos, 5, 0, "%i health", ship.get_health());
	}

	TitleHUD::TitleHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res)
			: HeadsUpDisplay(display, audio, res)
	{}

	void TitleHUD::render() const {

		static const char* long_time = "A long time ago,";
		static const char* asteroid_belt = "in an asteroid belt no so far away...";
		static const char* press_enter = "Press enter to continue...";
		static const int pos_x = display.get_width() / 35;
		static const int space_pos_y = display.get_height()/3;
		static const int press_pos_y = 2.5*display.get_height()/3;
		static const ALLEGRO_COLOR color_space = UI_COLOR_1;
		static const ALLEGRO_COLOR color_press = UI_COLOR_3;

		al_draw_text(res.get_font36(), color_space,
			pos_x, space_pos_y - 25, ALLEGRO_ALIGN_LEFT, long_time);

		al_draw_text(res.get_font36(), color_space,
			pos_x, space_pos_y + 25, ALLEGRO_ALIGN_LEFT, asteroid_belt);

		al_draw_text(res.get_font36(), color_press,
			pos_x, press_pos_y, ALLEGRO_ALIGN_LEFT, press_enter);
	}

	GameOverHUD::GameOverHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res)
			: HeadsUpDisplay(display, audio, res)
	{}

	void GameOverHUD::render() const {

		static const char* destroyed = "Your ship has been destroyed...";
		static const char* press = "Press enter to restart your mission";
		static const int pos_x = display.get_width()/10;
		static const int pos_y_destroyed = display.get_height()/3;
		static const int pos_y_press = 2*display.get_height()/3;
		static ALLEGRO_COLOR color_destroyed = UI_COLOR_1;
		static ALLEGRO_COLOR color_press = UI_COLOR_3;

		al_draw_text(res.get_font36(), color_destroyed,
			pos_x, pos_y_destroyed, 0, destroyed);

		al_draw_text(res.get_font36(), color_press,
			pos_x, pos_y_press, 0, press);
	}
	

	const string MainMenuHUD::text[][3] = {{
		string("PLAY"),
		string("OPTIONS"),
		string("QUIT")
	}, {
		string("EASY"),
		string("NORMAL"),
		string("HARD")
	}};

	MainMenuHUD::MainMenuHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res)
			: HeadsUpDisplay(display, audio, res)
			, active_text(0)
			, line(1)
	{}

	void MainMenuHUD::render() const {

		static const int pos_x = display.get_width()/2;
		static const int pos_y = display.get_height()/5;
		static const ALLEGRO_COLOR color = UI_COLOR_1;

		al_draw_text(res.get_font67(),
			color, pos_x, pos_y, ALLEGRO_ALIGN_CENTER, "Space Shooter");

		for (int line = 1; line < 4; ++line)
			draw_line(line);
	}

	void MainMenuHUD::draw_line(size_t line_) const {

		static const int width = static_cast<int>(display.get_width()/6);
		static const int height_base = static_cast<int>(display.get_height()/8);
		static const ALLEGRO_COLOR text_color = UI_COLOR_1;
		static const ALLEGRO_COLOR box_color = UI_COLOR_3;
		static const ALLEGRO_COLOR highlighted_box_color = UI_COLOR_2;
		
		float height = (3+line_) * height_base;

		al_draw_filled_rectangle(2 * width, height - 15, 6 * width, height + 25,
			line == line_? highlighted_box_color : box_color);
		
		al_draw_text(res.get_font36(), text_color, 3 * width, height,
			ALLEGRO_ALIGN_CENTER, text[active_text][line_-1].c_str());
	}


	const string OptionsHUD::text[] = {
		string("HEALTH BARS"),
		string("SOUND")
	};

	OptionsHUD::OptionsHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res,
			bool& HPbars)
			: HeadsUpDisplay(display, audio, res)
			, health_bars(HPbars)
			, line(1)
	{}

	void OptionsHUD::render() const {

		static const char* press_esc = "Press Escape to return to main menu";
		static const int press_esc_pos_x = display.get_width()/2;
		static const int press_esc_pos_y = static_cast<int>(0.95 * display.get_height());
		static const ALLEGRO_COLOR press_esc_color = UI_COLOR_3;

		static const int menu_pos_x = 3*display.get_width()/10;
		static const int menu1_pos_y = static_cast<int>(0.3 * display.get_height());
		static const int menu2_pos_y = static_cast<int>(0.6 * display.get_height());
		static const ALLEGRO_COLOR menu_color = UI_COLOR_1;

		for (int line = 1; line < 3; ++line)
				draw_line(line);

		al_draw_text(res.get_font18(), press_esc_color,
			press_esc_pos_x, press_esc_pos_y, ALLEGRO_ALIGN_CENTER, press_esc);
		

		al_draw_text(res.get_font18(), menu_color,
			menu_pos_x, menu1_pos_y, ALLEGRO_ALIGN_LEFT, health_bars ? "ON" : "OFF");

		al_draw_text(res.get_font18(), menu_color,
			menu_pos_x, menu2_pos_y, ALLEGRO_ALIGN_LEFT, audio.get_state() ? "ON" : "OFF");

	}

	void OptionsHUD::draw_line(size_t line_) const {

		static const int width = display.get_width();
		static const int h_base = 15 * display.get_height() / 100;

		static const ALLEGRO_COLOR highlighted_box = UI_COLOR_2;
		static const ALLEGRO_COLOR box = UI_COLOR_3;
		static const ALLEGRO_COLOR text_color = UI_COLOR_1;

		ALLEGRO_COLOR color = line == line_ ? highlighted_box : box;

		int scalar = 2 * line_ - 1;


		al_draw_filled_rectangle(0, scalar * h_base -5,
			2*width/3, scalar * h_base +40, color);

		al_draw_filled_rectangle(0.25 * width, (scalar + 1) * h_base - 5,
			width, (scalar + 1)*h_base +15, color);

		al_draw_text(res.get_font36(), text_color, width/10, scalar * h_base,
			ALLEGRO_ALIGN_LEFT, text[line_-1].c_str());
	}
}

#undef UI_COLOR_1
#undef UI_COLOR_2
#undef UI_COLOR_3