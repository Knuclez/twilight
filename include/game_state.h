#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "entities.h"
#include "scenes/scenes_main.h"

typedef struct {
    Scene current_scene;
    EntityKey player_key;
} GameState;

int initialize_game_state();
GameState* get_game_state_p();
Scene* get_current_scene_p(GameState *gs);

#endif
