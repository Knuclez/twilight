#ifndef ANIMATION_RSC_COMP
#define ANIMATION_RSC_COMP

#include "entities.h"

typedef struct {
    int resource_index;      // Índice en animation_rscs
    int current_frame;       // Frame actual (0 a frame_amount-1)
    float frame_timer;       // Timer para cambio de frame
} AnimationState;

// ===== API =====
int* animation_resource_indexes_get();
int animation_resource_index_get_from_key(EntityKey key);
void animation_resource_index_component_add(EntityKey key, int r_index);
int animation_rsc_index_component_list_init();

// ===== FRAME STATE API =====
int animation_state_get_frame(EntityKey key);
void animation_state_set_frame(EntityKey key, int frame);
float animation_state_get_timer(EntityKey key);
void animation_state_set_timer(EntityKey key, float timer);
void animation_state_update(EntityKey key, float delta_time, float frame_rate);
// Devuelve el índice del recurso de animación asociado a la entidad (o -1)
int animation_resource_get_rsc_index_from_key(EntityKey key);

#endif
