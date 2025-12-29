#include <stdio.h>
#include "game_manager.h"
#include "game_state.h"
#include "systems/movement.h"
#include "ecs/position_ecs.h"
#include "ecs/direction_ecs.h"
#include "ecs/is_cow_ecs.h"
#include "ecs/is_drawable_ecs.h"
#include "interface/screens/field_anims.h"


void initialize_ecs(){
    if(init_position_ecs() == 0){
	printf("failiure initializing position ecs \n");
    }
    init_is_cow_ecs();
    init_is_drawable_ecs();
    init_direction_ecs();

}

void initialize_game_systems(){
    initialize_ecs();

    if(initialize_game_state() == 0){
	printf("failiure initializing game state \n");
    }

}

void update(float delta){
    animate_clouds(delta);
    tick_movement_system(delta);
    return;
}


