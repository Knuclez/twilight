#include <string.h>
#include <stdio.h>
#include "tools/console.h"
#include "scenes/field_scene.h"
//#include "entities.h"
#include "game_state.h"

#include "components/direction_comp.h"
#include "components/direction_vec_comp.h"
#include "components/position_comp.h"
#include "components/size_comp.h"
#include "components/physical_bounds_comp.h"
#include "components/sprite_source_comp.h"
#include "components/animation_rsc_index.h"


void test_console(){
    const char prueba[] = "3,3,4,\n";
    int len = strlen(prueba); 
    printf("%d len:\n", len);
    interpret_command(prueba, len); 
}

void instance_rapp(){
    GameState *gs = get_game_state_p();
    EntityKey key = entity_create();
    int bitmask = 0;

    printf("index, %u\n", key.index);
    gs->player_key = key;
    position_component_add(key, 150, 100);
    size_component_add(key, 65, 80); 
    physical_bounds_component_add(key, 0, 0, 130, 85); 
    sprite_source_component_add(key, 1, 79, 84, 65, 81);  // ⭐ NUEVO: sprite_source
    direction_component_add(key);
    direction_vec_component_add(key, 0, 0);
    animation_resource_index_component_add(key, 0);
    bitmask |= HAS_ANIMATION_MASK;
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    bitmask |= IS_PLAYER_MASK;
    entity_add_bitmask(key, bitmask);
}

void instance_kuribo(){
    EntityKey key = entity_create();
    int bitmask = 0;

    position_component_add(key, 300, 500);
    size_component_add(key, 50, 50); 
    sprite_source_component_add(key, 2, 0, 0, 512, 512);  // ⭐ NUEVO: sprite_source
    direction_component_add(key);
    direction_vec_component_add(key, 0, 0);
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    entity_add_bitmask(key, bitmask);
}


void field_scene_load_ecs(){
    instance_rapp();
    instance_kuribo();
}


