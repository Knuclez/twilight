#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "entities.h"
#include "scenes/scenes_main.h"
#include "event_queues/collision_queue.h"

typedef struct {
    Scene current_scene;
    EntityKey player_key;
    CollisionQueue collision_queue;
    Entity entities[MAX_ENTITIES];
    int max_index;
} GameState;

int initialize_game_state();
GameState* get_game_state_p();
Scene* get_current_scene_p(GameState *gs);

#endif
