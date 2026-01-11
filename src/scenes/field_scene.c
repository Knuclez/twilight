#include <string.h>
#include <stdio.h>
#include "tools/console.h"
#include "scenes/field_scene.h"
#include "ecs/is_cow_ecs.h"
#include "ecs/is_cow_food_ecs.h"
#include "ecs/is_drawable_ecs.h"
#include "ecs/direction_ecs.h"
#include "ecs/position_ecs.h"
#include "ecs/size_ecs.h"
#include "ecs/source_rect_ecs.h"

#include "systems/digestion.h"

void instance_cow(int id, int x, int y){
    add_is_cow_component_to_id(id);
    add_position_component_to_id(id, x, y);  
    add_direction_component_to_id(id);
    add_size_component_to_id(id, 64, 64);
    add_is_drawable_component_to_id(id);
    add_source_rect_component_to_id(id, 66, 0 , 64, 64);
}

void instance_grass(int id, int x, int y){
    add_position_component_to_id(id, x, y);
    add_size_component_to_id(id, 64, 64);
    add_is_drawable_component_to_id(id);
    add_is_cow_food_component_to_id(id);
    add_source_rect_component_to_id(id, 0, 66, 64, 64);
}


void remove_grass(int id){
    remove_position_from_id(id);
    remove_size_from_id(id);
    remove_is_drawable_from_id(id);
    remove_is_cow_food_from_id(id);
}

void instance_tree(int id, int x, int y){
    add_position_component_to_id(id, x, y);
    add_size_component_to_id(id, 128, 128);
    add_is_drawable_component_to_id(id);
    add_source_rect_component_to_id(id, 66, 66, 64, 64);
}

void instance_poo(int id, int x, int y){
    add_position_component_to_id(id, x, y);
    add_size_component_to_id(id, 64, 64);
    add_is_drawable_component_to_id(id);
    add_source_rect_component_to_id(id, 132, 66, 64, 64);
}

void remove_field_entity(int id){
//naive grass removal
    if(is_id_cow_food(id) == 1){
	remove_grass(id);
    }
}

void test_console(){
    const char prueba[] = "3,3,4,\n";
    int len = strlen(prueba); 
    printf("%d len:\n", len);
    interpret_command(prueba, len); 
}

void instance_rapp(EntityKey *key){
   is_rapp_component_add(key);
}

void field_scene_load_ecs(){
    instance_cow(102, 500, 300);
    instance_cow(103, 100, 400);

    instance_cow(104, 700, 300);
    instance_cow(105, 50, 30);

    instance_grass(106, 200, 350);
    instance_tree(107, 300, 100);
    instance_rapp(new_entity());
}


