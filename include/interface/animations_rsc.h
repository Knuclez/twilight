#ifndef ANIMATIONS_RSC_H
#define ANIMATIONS_RSC_H

typedef struct{
    int sprite_x;
    int sprite_y;
    int x_offset;
    int frame_amount;
}AnimationRsc;

AnimationRsc* animation_rscs_get();

#endif
