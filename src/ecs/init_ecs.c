#include <stdio.h>
#include "ecs/init_ecs.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"
#include "ecs/size_ecs.h"
#include "ecs/source_rect_ecs.h"
#include "ecs/target_ecs.h"
#include "ecs/is_cow_ecs.h"
#include "ecs/is_cow_food_ecs.h"
#include "ecs/is_clickable_ecs.h"
#include "ecs/is_drawable_ecs.h"

void initialize_ecs(){
    if(init_position_ecs() == 0){
	printf("failiure initializing position ecs \n");
    }
    init_is_cow_ecs();
    init_is_cow_food_ecs();
    init_is_clickable_ecs();
    init_is_drawable_ecs();
    init_direction_ecs();
    init_size_ecs();
    init_source_rect_ecs();
    init_target_ecs();

}
