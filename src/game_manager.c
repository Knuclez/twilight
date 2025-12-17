#include <stdio.h>
#include "game_manager.h"
#include "game_state.h"
#include "systems/movement.h"
#include "ecs/position_ecs.h"
#include "interface/screens/field_anims.h"

void test_position_ecs(){
   Position *pos = get_id_associated_position(1);
   printf("pos x = %u \n", pos->x);
}

void initialize_ecs(){
    if(init_position_ecs() == 0){
	printf("failiure initializing position ecs \n");
    }

    register_position_to_id(1, 40, 100); 
    test_position_ecs();
}

void initialize_game_systems(){
    if(initialize_game_state() == 0){
	printf("failiure initializing game state \n");
    }

    initialize_ecs();
}

void update(float delta){
    animate_clouds(delta);
    move_all_to_right(delta);
    return;
}


