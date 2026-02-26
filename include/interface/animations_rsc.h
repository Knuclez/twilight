#ifndef ANIMATIONS_RSC_H
#define ANIMATIONS_RSC_H

#include "entities.h"

#define MAX_ANIM_CLIPS  32
#define MAX_ANIM_SETS   16
#define ANIM_SET_SLOTS  6   /* 5 CombatState slots + 1 moving slot */

/* Slot indices within an AnimationSet */
#define ANIM_SLOT_CHILL     0
#define ANIM_SLOT_CHASING   1
#define ANIM_SLOT_ATTACKING 2
#define ANIM_SLOT_ATTACKED  3
#define ANIM_SLOT_TREMBLE   4
#define ANIM_SLOT_MOVING    5  /* overrides CHILL when direction != DIR_IDLE */

/* A single animation sequence (one row/segment of a spritesheet) */
typedef struct {
    int   txtr_indx;    /* texture index */
    int   origin_x;     /* x of the first frame in the sheet */
    int   origin_y;     /* y of the first frame in the sheet */
    int   frame_w;      /* width of each frame */
    int   frame_h;      /* height of each frame */
    int   frame_count;  /* number of frames */
    int   x_stride;     /* horizontal advance per frame */
    int   y_stride;     /* vertical advance per direction row */
    float fps;          /* playback speed */
    int   loop;         /* 1 = loop, 0 = one-shot (hold last frame) */
} AnimationClip;

/* Maps entity states to clip indices */
typedef struct {
    int clip_indices[ANIM_SET_SLOTS];
} AnimationSet;

AnimationClip* animation_clips_get();
AnimationSet*  animation_sets_get();
void           animation_rscs_init();

/* Returns the clip index for a given entity state and direction */
int animation_get_clip_for_entity(int anim_set_index, CombatState cs, Direction dir);

#endif
