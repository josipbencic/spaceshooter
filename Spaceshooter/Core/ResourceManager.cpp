#include "ResourceManager.hpp"

#include <cassert>

namespace loop_tools {

  ResourceManager::ResourceManager() {

    p_ship = al_load_bitmap("art/spaceship.png");
    al_convert_mask_to_alpha(p_ship, al_map_rgb(255,0,255));
    assert(p_ship != NULL);

    p_explosion = al_load_bitmap("art/explosion.png");
    assert(p_explosion != NULL );

    p_comet = al_load_bitmap("art/comet.png");
    assert(p_comet != NULL );
    
    p_green_enemy_ship = al_load_bitmap("art/enemyspaceship1.png");
    al_convert_mask_to_alpha(p_green_enemy_ship, al_map_rgb(255,0,255));
    assert(p_green_enemy_ship != NULL );

    p_health_power_up = al_load_bitmap("art/french_key.png");
    assert(p_health_power_up != NULL);

    p_double_hit_power_up = al_load_bitmap("art/6dots.png");
    assert(p_double_hit_power_up != NULL);

    p_strong_missile = al_load_bitmap("art/green_blast1.png");
    assert(p_strong_missile != NULL);

    p_strong_missile_reversed = al_load_bitmap("art/red_blast2.png");
    assert(p_strong_missile_reversed != NULL);

    p_strong_green_power_up = al_load_bitmap("art/green_power_up.png");
    assert (p_strong_green_power_up != NULL);

    p_foreground = al_load_bitmap("art/foreground.png");
    assert (p_foreground != NULL);

    p_middleground = al_load_bitmap("art/middleground2.png");
    assert (p_middleground != NULL);

    p_background = al_load_bitmap("art/960background.png");
    al_convert_mask_to_alpha(p_background, al_map_rgb(0,0,0));
    assert (p_background != NULL);
    
    //  Loading fonts
    p_font18 = al_load_font("font/transformers.ttf", 18, 0);
    assert( p_font18 != NULL );

    p_font36 = al_load_font("font/transformers.ttf", 36, 0);
    assert( p_font36 != NULL);

    p_font67 = al_load_font("font/transformers.ttf", 67, 0);
    assert( p_font67 != NULL);
  }

  ResourceManager::~ResourceManager() {
    
    al_destroy_bitmap(p_ship);
    al_destroy_bitmap(p_comet);
    al_destroy_bitmap(p_explosion);
    al_destroy_bitmap(p_green_enemy_ship);
    al_destroy_bitmap(p_health_power_up);
    al_destroy_bitmap(p_double_hit_power_up);
    al_destroy_bitmap(p_strong_missile_reversed);
    al_destroy_bitmap(p_strong_missile);
    al_destroy_bitmap(p_strong_green_power_up);
    al_destroy_bitmap(p_foreground);
    al_destroy_bitmap(p_middleground);
    al_destroy_bitmap(p_background);

    al_destroy_font(p_font18);
    al_destroy_font(p_font36);
    al_destroy_font(p_font67);
  }


}