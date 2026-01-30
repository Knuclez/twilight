#include "interface/animations_rsc.h"

AnimationRsc animation_datas[10] = {0};

AnimationRsc* animation_rscs_get(){
    return animation_datas;
}

void animation_rscs_init(){
    AnimationRsc rapp_walk_rsc;
    rapp_walk_rsc.idle_x = 5;
    rapp_walk_rsc.x_offset = 66;
    rapp_walk_rsc.y_offset = 86;
    rapp_walk_rsc.frame_amount = 8;
    animation_datas[0] = rapp_walk_rsc;
}

