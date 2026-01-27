// include/interface/animations_rsc.h
#ifndef ANIMATIONS_RSC_H
#define ANIMATIONS_RSC_H

// ⭐ REFACTORIZADO: Solo datos de recurso global, sin sprite_x/sprite_y
typedef struct{
    int x_offset;        // Offset horizontal por frame
    int frame_amount;    // Cantidad de frames
}AnimationRsc;

AnimationRsc* animation_rscs_get();
AnimationRsc rapp_animation_rsc_get();
#endif
