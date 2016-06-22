/*
	Author: Josip Bencic
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <iostream>

//  Allegro headers
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
void __init_allegro__();

//  Project headers
#include "../Core/StateMachine.hpp"
#include "../Core/Display.hpp"
#include "../Core/Keyboard.hpp"
#include "../Core/Audio.hpp"
#include "../Core/ResourceManager.hpp"

using namespace loop_tools;
using namespace sprites;


int main() {

	__init_allegro__();

	Display			display;
	Audio			audio;
	ResourceManager resources;

	StateMachine state_machine(display, audio, resources);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display.get_display()));

    srand(time(NULL));

    while(!state_machine.done) {

		state_machine.update();

		while ( !al_event_queue_is_empty(event_queue)) {
			
			ALLEGRO_EVENT ev;
			al_get_next_event(event_queue, &ev);

			if ( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
				state_machine.done = true;
			} 
		}

		if ( state_machine.draw ) {

			state_machine.render();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	
	al_destroy_event_queue(event_queue);
}


void __init_allegro__() {

	//  Allegro initialization
	if ( !al_init() ) {
		std::cout << "failed to init allegro!" << std::endl;
		exit(-1);
	}

	//	Allegro Add-on initializations
	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
}
