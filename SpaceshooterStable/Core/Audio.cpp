#include <iostream>
#include <cassert>

#include "../Core/Audio.hpp"

namespace loop_tools {

	Audio::Audio() : state(true) {

		missile_launch = al_load_sample("audio/bullet.ogg");
		assert( missile_launch != NULL );

		explosion_sound = al_load_sample("audio/explosion.ogg");
		assert( explosion_sound != NULL );
		power_up = al_load_sample("audio/power-up.ogg");
		assert( power_up != NULL );

		background_music = al_load_sample("audio/song3.ogg");
		assert( background_music != NULL );

		al_reserve_samples(15);

		song_instance = al_create_sample_instance(background_music);
		assert( song_instance != NULL );

		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());
	}

	Audio::~Audio() {

		al_destroy_sample_instance(song_instance);
		al_destroy_sample(background_music);
		al_destroy_sample(power_up);
		al_destroy_sample(explosion_sound);
		al_destroy_sample(missile_launch);
	}
}
