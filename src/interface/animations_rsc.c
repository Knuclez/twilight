#include "interface/animations_rsc.h"

AnimationRsc animation_datas[10] = {0};

AnimationRsc* animation_rscs_get(){
    return animation_datas;
}

AnimationRsc rapp_animation_rsc_get(){
    AnimationRsc rapp_walk_rsc;
    rapp_walk_rsc.x_offset = 66;
    rapp_walk_rsc.frame_amount = 8;
    return rapp_walk_rsc;
}

