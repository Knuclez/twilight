#include "interface/animations_rsc.h"

AnimationClip g_clips[MAX_ANIM_CLIPS] = {0};
AnimationSet  g_anim_sets[MAX_ANIM_SETS] = {0};

AnimationClip* animation_clips_get() { return g_clips; }
AnimationSet*  animation_sets_get()  { return g_anim_sets; }

int animation_get_clip_for_entity(int anim_set_index, CombatState cs, Direction dir) {
    int slot = (int)cs;
    if (cs == CHILL && dir != DIR_IDLE) slot = ANIM_SLOT_MOVING;
    return g_anim_sets[anim_set_index].clip_indices[slot];
}

/* A single animation sequence (one row/segment of a spritesheet) 
typedef struct {
    int   txtr_indx;    //texture index
    int   origin_x;     // x of the first frame in the sheet
    int   origin_y;     // y of the first frame in the sheet 
    int   frame_w;      // width of each frame
    int   frame_h;      // height of each frame
    int   frame_count;  // number of frames
    int   x_stride;     // horizontal advance per frame
    int   y_stride;     // vertical advance per direction row
    float fps;          // playback speed
    int   loop;         // 1 = loop, 0 = one-shot (hold last frame)
} AnimationClip;

*/
void animation_rscs_init() {
    /* --- clips ----------------------------------------------------------- */
    /* 0: rapp walk  — 8 frames, 8 direction rows, rows start at y=84         */
    g_clips[0] = (AnimationClip){ 1, 79, 84, 65, 81, 8, 66, 86, 12.0f, 1 };
    /* 1: rapp idle  — single frame per direction row, rows start at y=84     */
    g_clips[1] = (AnimationClip){ 1,  5, 84, 65, 81, 1,  0, 86,  1.0f, 1 };
    /* 2: kuribo idle — single frame                                        */
    g_clips[2] = (AnimationClip){ 2,  0,  0, 512, 512, 1,  0, 512, 1.0f, 1 };
    /* 3: kuribo tremble — 2 frames one-shot                                */
    g_clips[3] = (AnimationClip){ 2,  0, 512, 512, 512, 1,  0, 512, 1.0f, 1 };

    /* --- sets ------------------------------------------------------------ */
    /* set 0: rapp (player) */
    g_anim_sets[0].clip_indices[ANIM_SLOT_CHILL]     = 1; /* idle */
    g_anim_sets[0].clip_indices[ANIM_SLOT_MOVING]    = 0; /* walk */
    g_anim_sets[0].clip_indices[ANIM_SLOT_CHASING]   = 0;
    g_anim_sets[0].clip_indices[ANIM_SLOT_ATTACKING] = 0;
    g_anim_sets[0].clip_indices[ANIM_SLOT_ATTACKED]  = 1;
    g_anim_sets[0].clip_indices[ANIM_SLOT_TREMBLE]   = 1;

    /* set 1: kuribo */
    g_anim_sets[1].clip_indices[ANIM_SLOT_CHILL]     = 2;
    g_anim_sets[1].clip_indices[ANIM_SLOT_MOVING]    = 2;
    g_anim_sets[1].clip_indices[ANIM_SLOT_CHASING]   = 2;
    g_anim_sets[1].clip_indices[ANIM_SLOT_ATTACKING] = 2;
    g_anim_sets[1].clip_indices[ANIM_SLOT_ATTACKED]  = 3;
    g_anim_sets[1].clip_indices[ANIM_SLOT_TREMBLE]   = 3; /* tremble */
}

