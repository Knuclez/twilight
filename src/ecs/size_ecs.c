#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/size_ecs.h"


//EL DIA QUE TENGA MAS ENTITYS QUE EL MAX VERE QUE ONDA SI LO HAGO HASH
//AHORA NO ES LO Q IMPORTA
ECBucket sizeIdList[LIST_SIZE];
Size sizes[MAX_ENTITIES];
int sizeCompAmount;

int get_size_component_amount(){
    return sizeCompAmount;
}

Size* get_size_by_index(int indx){
    return &sizes[indx];
}

Size* get_id_associated_size(int id){
    int size_indx = get_component_index_by_id(sizeIdList, id);
    if (size_indx == -1){
	return NULL;
    }
    return &sizes[size_indx];
}

int register_size(int n_w, int n_h){
   Size new; 
   new.w = n_w;
   new.h = n_h;
   sizes[sizeCompAmount] = new;
   sizeCompAmount ++;
   return sizeCompAmount - 1;
}

void add_size_component_to_id(int id, int w, int h){
    int index = register_size(w, h);
    //if(is_ec_registered(posIdList, id) == 1){
//	printf("entity %u allready registered \n", id);
  //  }
    register_ec(sizeIdList, id, index);
}

int init_size_ecs(){
    return init_ec_hash_list(sizeIdList);
}
