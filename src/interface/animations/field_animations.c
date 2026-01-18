#include "animations/field_animations.h"

typedef struct{
    int sprite_x;
    int sprite_y;
    int x_offset;
    int animation_lenght;
}AnimationData;

AnimationData rapp_anims[9];
//state is supposed to be an enum, so we could use it as index in an array;
void rapp_animations_load(int state, int x, int y, int n_x_offset, int max_frames){
    AnimationData new;
    new.sprite_x = x;
    new.sprite_y = y;
    new.x_offset = n_x_offset;
    new.animation_lenght = max_frames;
    rapp_anims[state] = new;
}
