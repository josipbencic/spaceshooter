#ifndef HEADSUPDISPLAY_HPP
#define HEADSUPDISPLAY_HPP

#include <string>
#include <algorithm>

namespace sprites {
	class Spaceship;
}

namespace loop_tools {

	class Display;
	class Audio;
	class ResourceManager;

	class HeadsUpDisplay {
	public:
		HeadsUpDisplay(
			Display& display,
			Audio& audio,
			ResourceManager& res);

		virtual ~HeadsUpDisplay() {}

		virtual void render() const = 0;

		virtual void set_line(int line) {}

	protected:
		Display&			display;
		Audio&				audio;
		ResourceManager&	res;

	};

	class TitleHUD: public HeadsUpDisplay {
	public:
		TitleHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res);
		virtual void render() const;
	};
	

	class GameOverHUD: public HeadsUpDisplay {
	public:
		GameOverHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res);
		virtual void render() const;

	};

	class PlayingHUD: public HeadsUpDisplay {
	public:
		PlayingHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res,
			sprites::Spaceship& ship);
		virtual void render() const;
	private:
		sprites::Spaceship& ship; 
	};

	class MainMenuHUD: public HeadsUpDisplay {
	public: 
		MainMenuHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res);
		
		virtual void render() const;

		void set_line(size_t line_) {
			line = line_;
		}

		void set_active_text(bool menu_or_diff) {
			active_text = menu_or_diff;
		}
		
		int get_current_line() const {
			return line;
		}

	private:
		void draw_line(size_t line) const;

		static const std::string text[][3];
		short active_text;
		size_t		line;


	};

	class OptionsHUD: public HeadsUpDisplay {
	public:
		OptionsHUD(
			Display& display,
			Audio& audio,
			ResourceManager& res,
			bool& HPbars);

		virtual void render() const;

		void set_line(size_t line_) {
			line = line_;
		}

		size_t get_line() const {
			return line;
		}
	private:
		void draw_line(size_t line) const;

		static const std::string text[];
		bool&	health_bars;
		size_t	line;
	};
}

#endif