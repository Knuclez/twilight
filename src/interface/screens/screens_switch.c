#include <stdio.h>
#include <SDL2/SDL.h>

#include "game_state.h"
#include "interface/screens_switch.h"
#include "interface/screens/field_screen.h"


void scene_switch_mouse_button(int clicked_entity_id){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
	case FIELD_SCENE:
	    field_screen_entity_clicked(clicked_entity_id, gs);
	    break;
    }
    return;
}


void scene_switch_input_event(SDL_Event event){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
	case FIELD_SCENE:
    	    field_screen_input_event(event);
	    break;
    }
}


void scene_switch_keydown(SDL_Event event){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
        case FIELD_SCENE:
	    field_screen_key_event(event);
	    break;
    }
}

void switch_init_screen(SceneType s_type){
    switch(s_type){
	case FIELD_SCENE:
	    init_field_screen();
	    break;
    }
    return;
}

void switch_scene_rendering(SDL_Renderer *renderer){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);
    SceneType type = cs->type;


    switch(type){
	case(FIELD_SCENE):
	    present_field_screen(renderer);
	    break;
    }
}


