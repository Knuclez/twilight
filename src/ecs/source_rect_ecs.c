#include <string.h>
#include <stdio.h>
#include "ecs/ec_hash_list.h"
#include "ecs/source_rect_ecs.h"

ECBucket sourceRectIdList[LIST_SIZE];
SourceRect source_rects[MAX_ENTITIES];
int sourceRectCompAmount;

int get_source_rect_comp_amount(){
    return sourceRectCompAmount;
}

SourceRect* get_id_associated_source_rect(int id){
    int indx = get_component_index_by_id(sourceRectIdList, id);
    if (indx == -1){
	printf("entity %u doesnt have an associated sourceRect \n", id);
	return NULL;
    }
    return &source_rects[indx];
}

int register_source_rect(int n_x, int n_y, int n_w, int n_h){
    SourceRect new;
    new.x = n_x;
    new.y = n_y;
    new.w = n_w;
    new.h = n_h;
    source_rects[sourceRectCompAmount] = new;
    sourceRectCompAmount ++;
    return sourceRectCompAmount -1;
}

void add_source_rect_component_to_id(int id, int x, int y, int w, int h){
    int indx = register_source_rect(x,y,w,h);
    register_ec(sourceRectIdList, id, indx);
    return;
}


void remove_source_rect_from_id(int id){
    //int indx = get_component_index_by_id(sourceRectIdList, id);
    change_ec(sourceRectIdList, id, -1);
}

void init_source_rect_ecs(){
     init_ec_hash_list(sourceRectIdList);
    return;
}
