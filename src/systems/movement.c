#include <stdio.h>
#include "systems/movement.h"
#include "ecs/position_ecs.h"
#include "ecs/is_cow_ecs.h"

void move_cows(float delta){
   int cows = get_cow_comp_amount();
   for(int i = 0; i < cows ; i++){
	Position* pos = get_position_by_index(i);
	if(pos == NULL){
	    printf("cow %u doesnt have an associated position \n", i);
	}
	float new_num = (50.0f * delta);
	pos->x += new_num;
   }
}

void tick_movement_system(float delta){
   move_cows(delta); 
}
