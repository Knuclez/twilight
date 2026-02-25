#include <stdio.h> 
#include <math.h>
#include "systems/combat.h"

#include "entities.h"  /* unified storage and helpers */
#include "game_state.h"
#include "systems/physics.h"


void combat_process_attack(EntityKey attacker_key){
    EntityKey key = entity_create();
    int bitmask = 0;

    Position att_pos = entity_get_position(attacker_key);
    DirectionVec att_dir = entity_get_direction_vec(attacker_key);
    PhysicalBounds pb = entity_get_physical_bounds(attacker_key);

    int radio = 10;
    int offset_x = att_dir.x * radio;
    int offset_y = att_dir.y * radio;

    /* configure the newly created entity directly */
    entity_set_position(key, att_pos.x + offset_x, att_pos.y + offset_y);
    entity_set_size(key, 40, 40);
    entity_set_physical_bounds(key, 0, 24, 40, 15);
    entity_set_lifetime(key, 1);
    entity_set_damage(key, 10);
    entity_set_sprite_source(key, 0, 198, 66, 62, 64);
    entity_set_direction_vec(key, 0, 0);

    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_DAMAGE_MASK;
    entity_add_bitmask(key, bitmask);
    individual_collider_check_collisions(key);
}

void combat_system_tick(GameState *gs){
    Entity *entities = gs->entities;
    int ent_count = gs->max_index;

    CollisionQueue collision_q = gs->collision_queue;
    int count = collision_queue_get_count(&collision_q);
    EntityKey attacker_key;
    EntityKey attacked_key;

    Entity *ent;
    for (int j = 0; j < ent_count; j++){
	ent = &entities[j];
	if(ent->combat_state == TREMBLE){
	    printf("%u timer\n",ent->combat_state_timer);
	    ent->combat_state_timer -= 1; 
	    if(ent->combat_state_timer <= 0){
		ent->combat_state = CHASING;
	    }    
	}
	if(ent->combat_state == CHASING){
	    Position target_position = entity_get_position(ent->target_key);
	    Position current_position = ent->position;
	    int x_diff = target_position.x - current_position.x;
	    int y_diff = target_position.y - current_position.y;
	    int mag = (int)sqrt((x_diff * x_diff) + (y_diff * y_diff));
	    if (mag == 0) continue;
	    int x_diff_norm = (x_diff * 10) / mag;
	    int y_diff_norm = (y_diff * 10) / mag;

	    entity_set_direction_vec(ent->key, x_diff_norm, y_diff_norm);
	    ent->bitmask |= IS_MOVING_MASK;
	}
    }

    for(int i = 0; i < count; i++){
	attacker_key = collision_q.collisions[i].entity1;
	attacked_key = collision_q.collisions[i].entity2;
	if(entity_get_combat_type(attacked_key) != MOB){continue;}
	int dc = entity_get_damage(attacker_key);
	int hc = entity_get_health(attacked_key);

	int new_health = hc - dc;
	entity_set_health(attacked_key, new_health);
	entity_set_combat_state(attacked_key, TREMBLE);
	entity_set_combat_state_timer(attacked_key, 100);
	if (new_health <= 0){
	    entity_deactivate(gs->entities, attacked_key);
	}
	printf("%u health\n", new_health);
    }
    return;
}
