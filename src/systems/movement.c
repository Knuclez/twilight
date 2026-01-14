#include <stdio.h>
#include <stdlib.h>

#include "systems/movement.h"
#include "entities.h"
#include "components/position_comp.h"

int movement_system_tick(void *v_ents, float delta){
    EntityKey *ents = (EntityKey*) v_ents;
    int ents_size = entities_amount();
    Position *positions = positions_get();
    for(int i = 0; i < ents_size; i++){
	EntityKey ent_key = (*(ents + i)); 
	int components_mask = ent_key.bitmask; 
	if(components_mask & IS_PLAYER_MASK){
	    int indx = position_index_get_from_key(ent_key);
	    Position pos = positions[i];
	    pos.x += (50 * delta);
	    positions[i] = pos;
	}
    }
    return 1;
}
