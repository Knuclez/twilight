#include "input_handler.h"
#include "game_state.h"
#include "entities.h"
#include "action_q.h"

#include "components/direction_comp.h"
#include "components/direction_vec_comp.h"

int moving_count = 0;

void event_key_down_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    int dir_indx = direction_index_get_from_key(player);

    DirectionVec *dvs = direction_vecs_get();
    int dvi = direction_vec_index_get_from_key(player);

    if(event.key.keysym.sym == SDLK_w){
	ds[dir_indx] = N;
	if(dvi >= 0) {dvs[dvi].y = -1;}
    }
    if(event.key.keysym.sym == SDLK_d){
	ds[dir_indx] = E;
	if(dvi >= 0) {dvs[dvi].x = 1;}
    }
    if(event.key.keysym.sym == SDLK_a){
	ds[dir_indx] = W;
	if(dvi >= 0) {dvs[dvi].x = -1;}
    }
    if(event.key.keysym.sym == SDLK_s){
	ds[dir_indx] = S;
	if(dvi >= 0) {dvs[dvi].y = 1;}
    }
    if(event.key.keysym.sym == SDLK_j){
	Action new;
	new.type = PLAYER_ATTACK;
	new.data = malloc(sizeof(int) * 2);
	*(new.data) = player.index;
	*(new.data + 1) = player.generation;
	queue_action(new);
    }
    return;
} 


void event_key_up_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    DirectionVec *dvs = direction_vecs_get();
    int dir_indx = direction_index_get_from_key(player);
    int dvi = direction_vec_index_get_from_key(player);

    if(event.key.keysym.sym == SDLK_w){
        ds[dir_indx] = IDLE; 
        if(dvi >= 0) {dvs[dvi].x = 0; dvs[dvi].y = 0;};
    }
    if(event.key.keysym.sym == SDLK_a){
        ds[dir_indx] = IDLE; 
        if(dvi >= 0) {dvs[dvi].x = 0; dvs[dvi].y = 0;};
    }
    if(event.key.keysym.sym == SDLK_s){
        ds[dir_indx] = IDLE; 
        if(dvi >= 0) {dvs[dvi].x = 0; dvs[dvi].y = 0;};
    }
    if(event.key.keysym.sym == SDLK_d){
        ds[dir_indx] = IDLE; 
        if(dvi >= 0) {dvs[dvi].x = 0; dvs[dvi].y = 0;};
    }

    return;
}

