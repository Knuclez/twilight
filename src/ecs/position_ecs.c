#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/position_ecs.h"


//EL DIA QUE TENGA MAS ENTITYS QUE EL MAX VERE QUE ONDA SI LO HAGO HASH
//AHORA NO ES LO Q IMPORTA
ECBucket posIdList[LIST_SIZE];
Position positions[MAX_ENTITIES];
int posCompAmount;

int get_position_component_amount(){
    return posCompAmount;
}

Position* get_position_by_index(int indx){
    return &positions[indx];
}

Position* get_id_associated_position(int id){
    int pos_indx = get_component_index_by_id(posIdList, id);
    if (pos_indx == -1){
	return NULL;
    }
    return &positions[pos_indx];
}

int register_position(int n_x, int n_y){
   Position new; 
   new.x = n_x;
   new.y = n_y;
   positions[posCompAmount] = new;
   posCompAmount ++;
   return posCompAmount - 1;
}

void register_position_to_id(int id, int x, int y){
    int index = register_position(x, y);
    //if(is_ec_registered(posIdList, id) == 1){
//	printf("entity %u allready registered \n", id);
  //  }
    register_ec(posIdList, id, index);
}

int init_position_ecs(){
    return init_ec_hash_list(posIdList);
}
