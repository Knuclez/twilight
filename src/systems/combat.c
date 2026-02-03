#include <stdio.h> 

#include "systems/combat.h"

#include "components/direction_comp.h"
#include "components/direction_vec_comp.h"
#include "components/position_comp.h"
#include "components/size_comp.h"
#include "components/sprite_source_comp.h"

void combat_process_attack(int attacker_indx, int attacker_generation){
    EntityKey attacker_key;
    attacker_key.index = attacker_indx;
    attacker_key.generation = attacker_generation;

    EntityKey key = entity_create();
    int bitmask = 0;
    Position att_pos = position_get_by_key(attacker_key);

    position_component_add(key, att_pos.x + 100, att_pos.y + 100);
    size_component_add(key, 40, 40);
    sprite_source_component_add(key, 0, 198, 66, 62, 64);  // ⭐ NUEVO: sprite_source
    direction_vec_component_add(key, 0, 0);
    bitmask |= IS_DRAWABLE_MASK;
    entity_add_bitmask(key, bitmask);
}
