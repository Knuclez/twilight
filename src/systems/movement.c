#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "systems/movement.h"
#include "systems/targeting.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"
#include "ecs/target_ecs.h"
#include "ecs/is_cow_ecs.h"
#include "ecs/is_cow_food_ecs.h"


Direction move_random(int i, Position *pos, float speed){
    srand(time(NULL) + i);
    int x_mod = (rand() % 3) - 1;
    int y_mod = (rand() % 3) - 1;
    pos->x += (x_mod * speed);
    pos->y += (y_mod * speed);
    Direction res = DOWN;
    if(x_mod == -1){
	res = LEFT;
    }else if(x_mod == 1){
	res = RIGHT;
    }
    return res;
}

Direction move_towards_target(int tgt_id, Position *pos, float speed){
    Position *tgt_pos = get_id_associated_position(tgt_id);
    if (tgt_pos == NULL){
	return DOWN;
    }
    int x_diff = tgt_pos->x - pos->x;
    int y_diff = tgt_pos->y - pos->y;
    if(abs(x_diff) + abs(y_diff) < 10){
	remove_target_entity(tgt_id);
	printf("llego al objetivo \n");
	return DOWN;
    }
    int norm_x = x_diff / abs(x_diff);
    int norm_y = y_diff / abs(y_diff);
    pos->x += (norm_x * speed);
    pos->y += (norm_y * speed);
    if (norm_x > 0){
	return RIGHT;
    }
    return LEFT; 
}

void move_cows(float delta){
    int cowsAmount = get_cow_comp_amount();
    int *cows = get_cow_ids();
    float speed = 50.0f * delta;

    for(int i = 0; i < cowsAmount ; i++){
	int cow_id = *(cows + i);
	Position* pos = get_id_associated_position(cow_id);
	Direction *dir = get_id_associated_direction(cow_id);
	Direction new_dir;

	int target_id = get_id_associated_target(cow_id);
	if(target_id != -1){
	    new_dir = move_towards_target(target_id, pos, speed);	    
	} else {
	    new_dir = move_random(i, pos, speed);
	    scan_for_food(cow_id, pos);
	}
	*dir = new_dir;
   }
}

void tick_movement_system(float delta){
   move_cows(delta); 
}
