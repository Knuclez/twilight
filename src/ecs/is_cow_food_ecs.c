#include <string.h>
#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/is_cow_food_ecs.h"


ECBucket isCowFoodIdList[LIST_SIZE];
int cowFood[MAX_ENTITIES];
int cowFoodCompAmount;

int get_cow_food_comp_amount(){
    return cowFoodCompAmount;
}

int* get_cow_food_entities(){
    return cowFood;
}

int is_id_cow_food(int id){
    int indx = get_component_index_by_id(isCowFoodIdList, id);
    if (indx == -1){
	return 0;
    }
    return 1;
}

void add_is_cow_food_component_to_id(int id){
    cowFood[cowFoodCompAmount] = id;
    register_ec(isCowFoodIdList, id, cowFoodCompAmount);
    cowFoodCompAmount += 1;
    return;
}

void remove_is_cow_food_from_id(int id){
    int cmp_indx = get_component_index_by_id(isCowFoodIdList, id);
    cowFood[cmp_indx] = -1;
    change_ec(isCowFoodIdList, id, -1);
}

void init_is_cow_food_ecs(){
     init_ec_hash_list(isCowFoodIdList);
    return;
}
