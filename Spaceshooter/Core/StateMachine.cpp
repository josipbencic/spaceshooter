#include "StateMachine.hpp"

#include "../Core/Display.hpp"
#include "../Core/Audio.hpp"
#include "../Core/ResourceManager.hpp"

#include "../Game/Spaceship.hpp"
#include "../Game/GameLogicManager.hpp"
#include "../Game/HeadsUpDisplay.hpp"

using namespace sprites;

namespace loop_tools {
	
	/*
		Each node is a State, and Actions are edges.
		For each state, there are actions that lead it into other states.
	*/
	const State StateMachine::adjecency_list[][13] = {
		{START, START, START, MM1, QUIT},
		{MM1, MM1, MM2, DIF1, QUIT},
		{MM2, MM1, MM3, OPT1, QUIT},
		{MM3, MM2, MM3, QUIT, QUIT},
		{OPT1, OPT1, OPT2, SWAP, MM1},
		{OPT2, OPT1, OPT2, SWAP, MM1},
		{OVER, OVER, OVER, PLAY, MM1},
		{PLAY, PLAY, PLAY, PLAY, OVER},
		{QUIT, QUIT, QUIT, QUIT, QUIT},
		{START, SWAP, SWAP, SWAP, SWAP},
		{DIF1, DIF1, DIF2, PLAY, MM1},
		{DIF2, DIF1, DIF3, PLAY, MM1},
		{DIF3, DIF2, DIF3, PLAY, MM1}
	};

	StateMachine::StateMachine(
		Display& display,
		Audio& audio,
		ResourceManager& res)
		: done(false)
		, display(display)
		, audio(audio)
		, res(res)
		, health_bars(true)
		, difficulty(Difficulty::EASY)
		, logic_manager(display, audio, res, difficulty, health_bars)
		, ship(logic_manager.get_ship())
		, state(State::START)
		, playingKey(ship)
		, interfaceKey()
		, keyboard(&interfaceKey)
		, titleHUD(display, audio, res)
		, mainMenuHUD(display, audio, res)
		, optionsHUD(display, audio, res, health_bars)
		, playingHUD(display, audio, res, ship)
		, gameOverHUD(display, audio, res)
		, HUD(&titleHUD)
	{}


	StateMachine::~StateMachine() {}

	void StateMachine::render() const {

		draw = false;

		if (state == State::PLAY)
			logic_manager.render();

		HUD->render();
	}

	void StateMachine::update() {

		draw = true;

		/*
			Player lost.
		*/
		if (state == State::PLAY) { 
		
			if (logic_manager.update() == -1) {
				set_state(State::OVER);
				return;
			}
		}

		Action action = keyboard->update();
		
		set_state(adjecency_list[state][action]);
	}

	void StateMachine::set_state(State new_state) {

		if (state == new_state) return;

		if (state == State::PLAY) {
			logic_manager.destroy_objects();
			audio.stop_playing();
		}

		switch (new_state) {

		case State::MM1:
			HUD = &mainMenuHUD;
			keyboard = &interfaceKey;
			mainMenuHUD.set_active_text(0);
			mainMenuHUD.set_line(1);
			break;

		case State::MM2:
			mainMenuHUD.set_line(2);
			break;
		
		case State::MM3:
			mainMenuHUD.set_line(3);
			break;

		case State::OPT1:
			HUD = &optionsHUD;
			keyboard = &interfaceKey;
			optionsHUD.set_line(1);
			break;

		case State::OPT2:
			optionsHUD.set_line(2);
			break;

		case State::OVER:
			HUD = &gameOverHUD;
			keyboard = &interfaceKey;
			break;

		case State::PLAY:
			HUD = &playingHUD;
			keyboard = &playingKey;
			logic_manager.reset();
			break;

		case State::QUIT:
			done = true;
			break;

		case State::SWAP:
			switch (state) {
			case State::OPT1:
				health_bars = !health_bars;
				break;

			case State::OPT2:
				audio.set_state(!audio.get_state());
				break;
			}
			return;

		case State::DIF1:
			HUD = &mainMenuHUD;
			keyboard = &interfaceKey;
			mainMenuHUD.set_active_text(1);
			mainMenuHUD.set_line(1);
			difficulty = Difficulty::EASY;
			break;

		case State::DIF2:
			mainMenuHUD.set_line(2);
			difficulty = Difficulty::MEDIUM;
			break;

		case State::DIF3:
			mainMenuHUD.set_line(3);
			difficulty = Difficulty::HARD;
			break;
		}
		state = new_state;
	}
}