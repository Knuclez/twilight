#include <string.h>
#include <stdio.h>
#include "tools/console.h"
#include "scenes/field_scene.h"
#include "entities.h"

#include "components/position_comp.h"
#include "components/texture_indx_comp.h"


void test_console(){
    const char prueba[] = "3,3,4,\n";
    int len = strlen(prueba); 
    printf("%d len:\n", len);
    interpret_command(prueba, len); 
}

void instance_rapp(){
    EntityKey key = entity_create();
    int bitmask = 0;
    position_component_add(key, 150, 100);
    texture_component_add(key, 1);
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    bitmask |= IS_PLAYER_MASK;
    entity_add_bitmask(key, bitmask);
}


void field_scene_load_ecs(){
    instance_rapp();
}


