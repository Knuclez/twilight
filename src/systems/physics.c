#include <stdio.h>
#include "systems/physics.h"

#include "game_state.h"
#include "entities.h"
#include "event_queues/collision_queue.h"


void individual_collider_check_collisions(EntityKey ent){
    GameState *gs = get_game_state_p();
    Entity *ents = entities;
    Entity to_check = ents[ent.index];
    Entity e;

    int left_side;
    int right_side;
    int top;
    int bottom;

    int l_s;
    int r_s;
    int t;
    int b;
    if(to_check.key.generation != ent.generation){
	printf("wrong generation for colliding check\n");
	return;
    }

    for (int i = 0; i < entities_max_index(); i++) {
        e = ents[i];
        if (e.key.index <= 0) continue;
        if (e.bitmask & HAS_COLIDER_MASK) {
	    left_side = to_check.position.x - to_check.physical_bounds.width + to_check.physical_bounds.x;
	    r_s = e.position.x + e.physical_bounds.width + to_check.physical_bounds.x;
	    if(left_side > r_s){
		continue;
	    }
	    right_side = to_check.position.x + to_check.physical_bounds.width + to_check.physical_bounds.x;
	    l_s = e.position.x - e.physical_bounds.width + to_check.physical_bounds.x;
	    if(right_side < l_s){
		continue;
	    }
	    top = to_check.position.y - to_check.physical_bounds.height + to_check.physical_bounds.y;
	    b = e.position.y + e.physical_bounds.height + to_check.physical_bounds.y;
	    if(top > b){
		continue;
	    }
	    bottom = to_check.position.y + to_check.physical_bounds.height + to_check.physical_bounds.y;
	    t = e.position.y - e.physical_bounds.height + to_check.physical_bounds.y;
	    if(bottom < t){
		continue;
	    }
	    
	    if(to_check.bitmask & IS_DAMAGE_MASK){
		collision_queue_add(&gs->collision_queue, ent, e.key);
	    }
	}
    } 
    return;
}
