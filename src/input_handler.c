#include "input_handler.h"
#include "game_state.h"
#include "entities.h"
#include "action_q.h"

int moving_count = 0;

void event_key_down_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Entity *p = entities_get() + player.index;

    if(event.key.keysym.sym == SDLK_w){
        p->direction = N;
        p->direction_vec.y = -1;
    }
    if(event.key.keysym.sym == SDLK_d){
        p->direction = E;
        p->direction_vec.x = 1;
    }
    if(event.key.keysym.sym == SDLK_a){
        p->direction = W;
        p->direction_vec.x = -1;
    }
    if(event.key.keysym.sym == SDLK_s){
        p->direction = S;
        p->direction_vec.y = 1;
    }
    if(event.key.keysym.sym == SDLK_j){
        Action new_act = {0};
        new_act.type = PLAYER_ATTACK;
        new_act.data.attacker_key = player;
        queue_action(new_act);
    }
    return;
} 


void event_key_up_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Entity *p = entities_get() + player.index;

    if(event.key.keysym.sym == SDLK_w){
        p->direction = IDLE;
        p->direction_vec.x = 0; p->direction_vec.y = 0;
    }
    if(event.key.keysym.sym == SDLK_a){
        p->direction = IDLE;
        p->direction_vec.x = 0; p->direction_vec.y = 0;
    }
    if(event.key.keysym.sym == SDLK_s){
        p->direction = IDLE;
        p->direction_vec.x = 0; p->direction_vec.y = 0;
    }
    if(event.key.keysym.sym == SDLK_d){
        p->direction = IDLE;
        p->direction_vec.x = 0; p->direction_vec.y = 0;
    }

    return;
}

