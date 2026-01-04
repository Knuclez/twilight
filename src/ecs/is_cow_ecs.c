#include <string.h>
#include "ecs/is_cow_ecs.h"
#include "ecs/ec_hash_list.h"

int cows[MAX_ENTITIES];
int cowCompAmount;

int get_cow_comp_amount(){
    return cowCompAmount;
}

int* get_cow_ids(){
    return cows;
}

void add_is_cow_component_to_id(int id){
    cows[cowCompAmount] = id;
    cowCompAmount += 1;
    return;
}


void init_is_cow_ecs(){
    memset(cows, 0xCC, sizeof(int) * MAX_ENTITIES);
    return;
}
