#include <string.h>
#include <stdio.h>
#include "tools/console.h"
#include "scenes/field_scene.h"
//#include "entities.h"
#include "game_state.h"

#include "components/direction_comp.h"
#include "components/position_comp.h"
#include "components/sprite_source_comp.h"
#include "components/texture_indx_comp.h"
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

    gs->player_key = key;
    position_component_add(key, 150, 100);
    sprite_source_component_add(key, 79, 84, 65, 81);  // ⭐ NUEVO: sprite_source
    direction_component_add(key);
    texture_component_add(key, 1);
    animation_resource_index_component_add(key, 0);
    bitmask |= HAS_ANIMATION_MASK;
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    bitmask |= IS_PLAYER_MASK;
    entity_add_bitmask(key, bitmask);
}


void field_scene_load_ecs(){
    instance_rapp();
}


