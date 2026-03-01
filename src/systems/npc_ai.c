#include "systems/npc_ai.h"
#include <stdio.h> 
#include <math.h> 

#include "game_state.h"

typedef struct {
    DirectionVec direction_vector;
    int magnitude;
} VectorAndMagnitude;

VectorAndMagnitude vector_to_target_position_size_10(Position current_position, Position target_position){
    int x_diff = target_position.x - current_position.x;
    int y_diff = target_position.y - current_position.y;
    int mag = (int)sqrt((x_diff * x_diff) + (y_diff * y_diff));
    int x_diff_norm = (x_diff * 10) / mag;
    int y_diff_norm = (y_diff * 10) / mag;
    DirectionVec vec = (DirectionVec){x_diff_norm, y_diff_norm};
    return (VectorAndMagnitude){vec, mag};
}

void tick_npc_ai(GameState *gs){
    Entity *entities = gs->entities;
    int ent_count = gs->max_index;
    Entity *ent;

    for (int j = 0; j < ent_count; j++){
	ent = &entities[j];
	if(ent->key.index == 0){continue;}
	if(ent->combat_state == TREMBLE){
	    printf("%u timer\n",ent->combat_state_timer);
	    ent->combat_state_timer -= 1; 
	    if(ent->combat_state_timer <= 0){
		entity_set_combat_state(ent->key, CHASING);
		ent->bitmask |= IS_MOVING_MASK;
	    }    
	}
	if(ent->combat_state == CHASING){
	    printf("chasing\n");
	    Position target_position = entity_get_position(ent->target_key);
	    Position current_position = ent->position;
	    VectorAndMagnitude vec_and_mag = vector_to_target_position_size_10(current_position, target_position);
	    if (vec_and_mag.magnitude <= 15) {
		entity_set_direction_vec(ent->key, 0, 0);
		ent->bitmask &= ~IS_MOVING_MASK;
		ent->combat_state = ATTACKING;
		continue;
	    }
	    entity_set_direction_vec(ent->key, vec_and_mag.direction_vector.x, vec_and_mag.direction_vector.y);
	}
	if(ent->combat_state == ATTACKING){
	}
    }
 
}
