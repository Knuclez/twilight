#include <string.h>
#include <stdio.h>
#include "tools/console.h"
#include "scenes/field_scene.h"
//#include "entities.h"
#include "game_state.h"

#include "entities.h"  /* unified entity data and helpers */


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
    entity_set_position(key, 150, 100);
    entity_set_size(key, 65, 80);
    entity_set_physical_bounds(key, 0, 0, 130, 85);
    entity_set_sprite_source(key, 1, 79, 84, 65, 81);
    entity_set_direction(key, IDLE);
    entity_set_direction_vec(key, 0, 0);
    entity_set_animation(key, 0);

    bitmask |= HAS_ANIMATION_MASK;
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    bitmask |= IS_PLAYER_MASK;
    bitmask |= HAS_COLIDER_MASK;
    entity_add_bitmask(key, bitmask);
}

void instance_kuribo(){
    EntityKey key = entity_create();
    int bitmask = 0;

    entity_set_position(key, 300, 500);
    entity_set_size(key, 50, 50);
    entity_set_physical_bounds(key, 0, 0, 100, 100);
    entity_set_sprite_source(key, 2, 0, 0, 512, 512);
    entity_set_direction(key, IDLE);
    entity_set_direction_vec(key, 0, 0);
    bitmask |= IS_DRAWABLE_MASK;
    bitmask |= IS_MOVABLE_MASK;
    entity_add_bitmask(key, bitmask);
}


void field_scene_load_ecs(){
    instance_rapp();
    instance_kuribo();
}


