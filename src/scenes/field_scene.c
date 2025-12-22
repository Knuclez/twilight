#include "scenes/field_scene.h"
#include "ecs/is_cow_ecs.h"
#include "ecs/is_drawable_ecs.h"
#include "ecs/position_ecs.h"

void instance_cow(int id, int x, int y){
    add_is_cow_component_to_id(id);
    add_position_component_to_id(id, x, y);  
    add_is_drawable_component_to_id(id);
}

void field_scene_load_ecs(){
    instance_cow(102, 10, 300);
    instance_cow(103, 100, 400);
}
