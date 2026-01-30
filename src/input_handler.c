#include "input_handler.h"
#include "game_state.h"
#include "entities.h"
#include "components/direction_comp.h"

void event_key_down_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    int dir_indx = direction_index_get_from_key(player);
    if(event.key.keysym.sym == SDLK_w){
	ds[dir_indx] = N;
    }
    if(event.key.keysym.sym == SDLK_d){
	ds[dir_indx] = E;
    }
    if(event.key.keysym.sym == SDLK_a){
	ds[dir_indx] = W;
    }
    if(event.key.keysym.sym == SDLK_s){
	ds[dir_indx] = S;
    }
    return;
}


void event_key_up_handle(SDL_Event event){
    EntityKey player = (get_game_state_p())->player_key;
    Direction *ds = directions_get();
    int dir_indx = direction_index_get_from_key(player);
	printf("esta frnando\n");
    ds[dir_indx] = IDLE; 
    return;
}

