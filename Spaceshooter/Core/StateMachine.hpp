#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "../Core/Keyboard.hpp"

#include "../Game/GameLogicManager.hpp"
#include "../Game/HeadsUpDisplay.hpp"

namespace sprites {
  class Spaceship;
}

namespace loop_tools {

  class Display;
  class Audio;
  class ResourceManager;

  enum State {
    START = 0,
    MM1 = 1,
    MM2 = 2,
    MM3 = 3,
    OPT1 = 4,
    OPT2 = 5,
    OVER = 6,
    PLAY = 7,
    QUIT = 8,
    SWAP = 9,
    DIF1 = 10,
    DIF2 = 11,
    DIF3 = 12
  };

  enum Difficulty {
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
  };

  class StateMachine {

    friend class Keyboard;
  public:
    StateMachine(
      Display& display,
      Audio& audio,
      ResourceManager& res);

    ~StateMachine();

    inline State get_state() const { return state; }
    void set_state(State new_state);
    void render() const;
    void update();

    bool done;
    mutable bool draw;

  private:

    /* Graph representing state swapping */
    static const State  adjecency_list[][13];

    Display&            display;
    Audio&              audio;
    ResourceManager&    res;

    bool                health_bars;
    Difficulty          difficulty;

    GameLogicManager    logic_manager;

    sprites::Spaceship& ship;

    State               state;

    PlayingKeyboard     playingKey;
    InterfaceKeyboard   interfaceKey;
    Keyboard*           keyboard;

    TitleHUD            titleHUD;
    MainMenuHUD         mainMenuHUD;
    OptionsHUD          optionsHUD;
    PlayingHUD          playingHUD;
    GameOverHUD         gameOverHUD;

    // needs to be last
    HeadsUpDisplay*     HUD;
  };
}
#endif