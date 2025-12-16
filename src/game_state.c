#include "game_state.h"

GameState game_state;

int initialize_game_state(){
    initialize_scene(&game_state.current_scene);
    return 1;
}

GameState* get_game_state_p(){
    return &game_state;
}

Scene* get_current_scene_p(GameState *gs){
    return &gs->current_scene;
}
