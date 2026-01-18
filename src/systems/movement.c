#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "systems/movement.h"
//#include "entities.h"
#include "components/direction_comp.h"
#include "components/position_comp.h"


int movement_system_tick(void *v_ents, float delta){
    EntityKey *ents = (EntityKey*) v_ents;
    int ents_size = entities_amount();
    Position *positions = positions_get();
    Direction * directions = directions_get();

    EntityKey ent_key; 
    int components_mask; 
    int speed = 100;
    for(int i = 0; i < ents_size; i++){
	ent_key = (*(ents + i)); 
	components_mask = ent_key.bitmask; 

	if((components_mask & IS_MOVABLE_MASK) == 0){
	    continue;
	}

	int pos_indx = position_index_get_from_key(ent_key);
	int dir_indx = direction_index_get_from_key(ent_key);
	Position pos = positions[pos_indx];
	Direction dir = directions[dir_indx];
	if(components_mask & IS_PLAYER_MASK){
	    int mov = speed  * delta;
	    switch(dir){
		case N:
		    break;
		case E:
		    pos.x += mov;
		    break;
		case W:
		    pos.x -= mov;
		    break;
	    }
	    positions[pos_indx] = pos;
	}

    }
    return 1;
}
