#include <stdio.h>
#include <SDL2/SDL.h>

#include "game_state.h"
#include "interface/scenes.h"

#include "interface/screens/field_screen.h"

SceneType last_scene_type = -1;

void scene_switch_mouse_button(int clicked_entity_id){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
	case FIELD_SCREEN:
	    field_screen_entity_clicked(clicked_entity_id, gs);
	    break;
    }
    return;
}


void scene_switch_input_event(SDL_Event event){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
	case FIELD_SCREEN:
    	    field_screen_input_event(event);
	    break;
    }
}


void scene_switch_keydown(SDL_Event event){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);

    switch(cs->type){
        case FIELD_SCREEN:
	    field_screen_key_event(event);
	    break;
    }
}

void switch_gui_entities_loading(SceneType s_type){
    switch(s_type){
	case FIELD_SCREEN:
	    load_field_screen_gui_entities();
	    break;
    }
    return;
}

void switch_scene_rendering(SDL_Renderer *renderer){
    GameState *gs = get_game_state_p();
    Scene *cs = get_current_scene_p(gs);
    SceneType type = cs->type;

    if (last_scene_type != type){
	switch_gui_entities_loading(type);
	last_scene_type = type;
    }

    switch(type){
	case(FIELD_SCREEN):
	    present_field_screen(renderer);
	    break;
    }
}

void initialize_scene(Scene *scene){
    scene->type = FIELD_SCREEN;
    if(scene->type != 0){
	printf("fallo al inicializar la escena");
    }
    switch_gui_entities_loading(FIELD_SCREEN);
    return;
}

void finalize_scene(Scene *scene){
    switch(scene->type){
	case FIELD_SCREEN:
	   break;
    }
}

