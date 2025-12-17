#include <stdio.h>
#include "systems/movement.h"
#include "ecs/position_ecs.h"

void move_all_to_right(float delta){
   int amount = get_position_component_amount();
   for(int i = 0; i < amount ; i++){
	Position* pos = get_position_by_index(i);
	float new_num = (50.0f * delta);
	pos->x += new_num;
   }
}
