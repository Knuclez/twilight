// include/interface/animations_rsc.h
#ifndef ANIMATIONS_RSC_H
#define ANIMATIONS_RSC_H

// ⭐ REFACTORIZADO: Solo datos de recurso global, sin sprite_x/sprite_y
typedef struct{
    int idle_x;
    int x_offset;        // Offset horizontal por frame
    int y_offset;        // Offset vertical por frame
    int frame_amount;    // Cantidad de frames
}AnimationRsc;

AnimationRsc* animation_rscs_get();
void animation_rscs_init();
#endif
