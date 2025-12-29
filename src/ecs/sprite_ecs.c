#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/sprite_ecs.h"

ECBucket sprIdList[LIST_SIZE];
SpriteRect spritePositions[MAX_ENTITIES];
int sprCompAmount;

int get_sprite_component_amount(){
    return sprCompAmount;
}

SpriteRect* get_spr_rect_by_index(int indx){
    return &spritePositions[indx];
}

SpriteRect* get_id_associated_spr_rect(int id){
    int spr_indx = get_component_index_by_id(sprIdList, id);
    if (spr_indx == -1){
	return NULL;
    }
    return &spritePositions[spr_indx];
}

int register_spr_rect(int n_w, int n_h, int n_x, int n_y){
   SpriteRect new; 
   new.w = n_w;
   new.h = n_h;
   new.x = n_x;
   new.y = n_y;
   spritePositions[sprCompAmount] = new;
   sprCompAmount ++;
   return sprCompAmount - 1;
}

void add_spr_rect_component_to_id(int id,int w, int h, int x, int y){
    int index = register_spr_rect(w, h, x, y);
    //if(is_ec_registered(posIdList, id) == 1){
//	printf("entity %u allready registered \n", id);
  //  }
    register_ec(sprIdList, id, index);
}

int init_spr_rect_ecs(){
    return init_ec_hash_list(sprIdList);
}

