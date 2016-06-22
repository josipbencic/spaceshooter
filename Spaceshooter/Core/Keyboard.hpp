#ifndef KEYBOARD_HPP_INCLUDED
#define KEYBOARD_HPP_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>

#include <cstring>

namespace sprites {
	class Spaceship;
}

namespace loop_tools {

	class Audio;

	enum Action {
		NOTHING = 0,
		UP = 1,
		DOWN = 2,
		ENTER = 3,
		ESCAPE = 4
	};

	/*
		Keyboard class triggers actions and switches states.
	*/
	class Keyboard {

	public:
		Keyboard();
		virtual ~Keyboard() {}
		
		Action update();

	protected:
		virtual Action input() = 0;
		
		ALLEGRO_KEYBOARD_STATE  state;

	private:
		Keyboard(const Keyboard&);
		const Keyboard& operator= (const Keyboard&) {}
	};

	class InterfaceKeyboard : public Keyboard {
	public:
		InterfaceKeyboard()
			: Keyboard() {

			memset(last_pressed, 0, sizeof last_pressed);
		}
	private:
		virtual Action input();

		bool last_pressed[8];
	};

	class PlayingKeyboard : public Keyboard {
	public:	
		PlayingKeyboard(sprites::Spaceship& ship)
			: Keyboard(), ship(ship)
		{}

	private:
		virtual Action input();

		sprites::Spaceship& ship;
	};
}

#endif