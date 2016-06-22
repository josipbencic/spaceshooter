#ifndef AUDIO_HPP_INCLUDED
#define AUDIO_HPP_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

namespace loop_tools {

	/*

		Wrapper class for allegro audio system
		Each sprite can call it's audio function.
	*/
	class Audio {
	private:
		typedef ALLEGRO_SAMPLE* p_sample;
	public:
		/*	
			Ctor - owns all the .ogg files (slow, to be called before main loop)
		*/
		Audio();

		/*
			Dtor - destroys all the .ogg files (slow, to be called at the end)
		*/
		~Audio();

		/*
			Self-explainatory functions that play samples when called.
			Background music plays on infinite loop, while others last shortly.

		*/
		void play_power_up() const {
			if (state) al_play_sample(power_up, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}

		void play_explosion() const {
			if (state) al_play_sample(explosion_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}

		void play_missile_launch() const {
			if (state) al_play_sample(missile_launch, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		}

		void play_background_music() const {
			if (state) al_play_sample_instance(song_instance);
		}

		void stop_playing() const {
			if (state) al_stop_sample_instance(song_instance);
		}

		void set_state(bool in) const {
			state = in;
		}
		
		bool get_state() const {
			return state;
		}

	private:
		/*
			Allegro sample variables for each sound 
			that is possible to play inside the game
		*/
        p_sample					background_music;
        p_sample					explosion_sound;
		p_sample					missile_launch;
		p_sample					power_up;
        ALLEGRO_SAMPLE_INSTANCE*	song_instance;
		mutable bool				state;
	};
}


#endif