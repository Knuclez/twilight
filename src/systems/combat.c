#include <stdio.h> 

#include "systems/combat.h"
#include "entities.h"  /* unified storage and helpers */
#include "systems/physics.h"


void combat_process_attack(EntityKey attacker_key){
    EntityKey key = entity_create();
    int bitmask = 0;

    Position att_pos = entity_get_position(attacker_key);
    DirectionVec att_dir = entity_get_direction_vec(attacker_key);
    PhysicalBounds pb = entity_get_physical_bounds(attacker_key);

    int radio = 100;
    int offset_x = att_dir.x * radio;
    int offset_y = att_dir.y * radio;

    /* configure the newly created entity directly */
    entity_set_position(key, att_pos.x + offset_x, att_pos.y + offset_y);
    entity_set_size(key, 40, 40);
    entity_set_physical_bounds(key, 0, 24, 40, 15);
    entity_set_lifetime(key, 1);
    entity_set_sprite_source(key, 0, 198, 66, 62, 64);
    entity_set_direction_vec(key, 0, 0);

    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_COMBAT_ENT_MASK;
    entity_add_bitmask(key, bitmask);
    individual_collider_check_collisions(key);
}

void tick_combat(){
}
