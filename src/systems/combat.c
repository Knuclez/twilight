#include <stdio.h> 

#include "systems/combat.h"

#include "entities.h"
#include "components/direction_vec_comp.h"
#include "components/position_comp.h"
#include "components/size_comp.h"
#include "components/physical_bounds_comp.h"
#include "components/sprite_source_comp.h"
#include "components/lifetime_comp.h"

void combat_process_attack(int attacker_indx, int attacker_generation){
    EntityKey attacker_key;
    attacker_key.index = attacker_indx;
    attacker_key.generation = attacker_generation;

    EntityKey key = entity_create();
    int bitmask = 0;
    Position att_pos = position_get_by_key(attacker_key);
    DirectionVec att_dir = direction_vec_get_by_key(attacker_key);
    PhysicalBounds pb = physical_bounds_get_by_key(attacker_key);

    int radio = 100;
    int attacker_center_x = att_pos.x + pb.x + (pb.width / 2);
    int attacker_center_y = att_pos.y + pb.y + (pb.height / 2);
    int offset_x = att_dir.x * radio;
    int offset_y = att_dir.y * radio;

    position_component_add(key, att_pos.x + offset_x, att_pos.y + offset_y);
    size_component_add(key, 40, 40);
    physical_bounds_component_add(key, 0, 0, 40, 40); 
    lifetime_component_add(key, 5);
    sprite_source_component_add(key, 0, 198, 66, 62, 64);  // ⭐ NUEVO: sprite_source
    direction_vec_component_add(key, 0, 0);
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_COMBAT_ENT_MASK;
    entity_add_bitmask(key, bitmask);
}

void tick_combat(){
}
