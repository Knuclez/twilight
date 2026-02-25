// src/systems/movement.c
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "systems/movement.h"
#include "entities.h"  /* unified storage, includes bitmask macros */

/* old SoA component includes have been removed; component data now lives
   directly inside the Entity struct. */

int movements_process_frame(void *v_ents, float delta){
    /* iterate over all alive entities */
    Entity *ents = (Entity*) v_ents;
    int max = entities_max_index();
    int speed = 70;

    //print_bitmask_debug(ents, e->key);
    for (int i = 0; i < max; i++) {
        Entity *e = &ents[i];
        if (e->key.index < 0) continue;         /* empty slot */
        if ((e->bitmask & IS_MOVING_MASK) == 0) continue;

        /* apply movement directly on the entity fields */
        /* direction_vec is scaled by 10, so divide by 10 here */
        e->position.x += (int)(speed * delta) * e->direction_vec.x ;
        e->position.y += (int)(speed * delta) * e->direction_vec.y ;
    }
    
    return 1;
}
