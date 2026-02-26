#include "input_handler.h"
#include "game_state.h"
#include "entities.h"
#include "action_q.h"

void event_key_down_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Entity *p = entities_get() + player.index;

    if(event.key.keysym.sym == SDLK_w){
        p->direction |= DIR_N;
        p->direction_vec.y = -10;
    }
    if(event.key.keysym.sym == SDLK_d){
        p->direction |= DIR_E;
        p->direction_vec.x = 10;
    }
    if(event.key.keysym.sym == SDLK_a){
        p->direction |= DIR_W;
        p->direction_vec.x = -10;
    }
    if(event.key.keysym.sym == SDLK_s){
        p->direction |= DIR_S;
        p->direction_vec.y = 10;
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
        p->direction &= ~DIR_N;
        if(!(p->direction & (DIR_N | DIR_S))) p->direction_vec.y = 0;
    }
    if(event.key.keysym.sym == SDLK_a){
        p->direction &= ~DIR_W;
        if(!(p->direction & (DIR_W | DIR_E))) p->direction_vec.x = 0;
    }
    if(event.key.keysym.sym == SDLK_s){
        p->direction &= ~DIR_S;
        if(!(p->direction & (DIR_N | DIR_S))) p->direction_vec.y = 0;
    }
    if(event.key.keysym.sym == SDLK_d){
        p->direction &= ~DIR_E;
        if(!(p->direction & (DIR_W | DIR_E))) p->direction_vec.x = 0;
    }
    return;
}


/*
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
*/
