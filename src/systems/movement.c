#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "systems/movement.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"
#include "ecs/is_cow_ecs.h"


Direction move_random(int i, Position *pos, float speed, float delta){
    srand(time(NULL) + i);
    int x_mod = (rand() % 3) - 1;
    int y_mod = (rand() % 3) - 1;
    pos->x += (x_mod * speed * delta);
    pos->y += (y_mod * speed * delta);
    Direction res = DOWN;
    if(x_mod == -1){
	res = LEFT;
    }else if(x_mod == 1){
	res = RIGHT;
    }
    return res;
}

void move_cows(float delta){
   int cows = get_cow_comp_amount();
   for(int i = 0; i < cows ; i++){
	Position* pos = get_position_by_index(i);
	Direction *dir = get_direction_by_index(i);
	if(pos == NULL){
	    printf("cow %u doesnt have an associated position \n", i);
	}
	Direction new_dir = move_random(i, pos, 50.0f, delta);
	if(new_dir != *dir){
	    //change_sprite();
	    *dir = new_dir;
	}
   }
}

void tick_movement_system(float delta){
   move_cows(delta); 
}
