#include <stdio.h>
#include "storage_structures/ec_hash_list.h"
#include "components/animation_rsc_index.h"
#include "interface/animations_rsc.h"

ECBucket animRscIdList[LIST_SIZE];
AnimationState anim_states[MAX_ENTITIES];
int animRscCompAmount;

int animation_rsc_register(int resource_index){
   anim_states[animRscCompAmount].resource_index = resource_index;
   anim_states[animRscCompAmount].current_frame = 0;
   anim_states[animRscCompAmount].frame_timer = 0.0f;
   animRscCompAmount ++;
   return animRscCompAmount - 1;
}

//PUBLICS
int* animation_resource_indexes_get(){
    // Helper para obtener solo los índices (compatibilidad)
    static int temp_indexes[MAX_ENTITIES];
    for (int i = 0; i < animRscCompAmount; i++) {
        temp_indexes[i] = anim_states[i].resource_index;
    }
    return temp_indexes;
}

int animation_resource_index_get_from_key(EntityKey key){
    int indx = component_index_get(animRscIdList, key);
    return indx;
}

void animation_resource_index_component_add(EntityKey key, int r_index){
    int iindex = animation_rsc_register(r_index);
    ec_register(animRscIdList, key, iindex);
}


void anim_rsc_component_remove(EntityKey key){
    ec_value_change(animRscIdList, key, -1);
}

int animation_rsc_index_component_list_init(){
    animRscCompAmount = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        anim_states[i].resource_index = -1;
        anim_states[i].current_frame = 0;
        anim_states[i].frame_timer = 0.0f;
    }
    return ec_hash_list_init(animRscIdList);
}

// ===== FRAME STATE MANAGEMENT =====
int animation_state_get_frame(EntityKey key){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        return anim_states[comp_idx].current_frame;
    }
    return 0;
}

void animation_state_set_frame(EntityKey key, int frame){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        int rsc_idx = anim_states[comp_idx].resource_index;
        if (rsc_idx >= 0 && rsc_idx < 10) {
            AnimationRsc* rscs = animation_rscs_get();
            int max_frame = rscs[rsc_idx].frame_amount - 1;
            anim_states[comp_idx].current_frame = (frame > max_frame) ? max_frame : frame;
        }
    }
}

float animation_state_get_timer(EntityKey key){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        return anim_states[comp_idx].frame_timer;
    }
    return 0.0f;
}

void animation_state_set_timer(EntityKey key, float timer){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        anim_states[comp_idx].frame_timer = timer;
    }
}

void animation_state_update(EntityKey key, float delta_time, float frame_rate){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        // DEBUG: ver valores (temporal)
        anim_states[comp_idx].frame_timer += delta_time;
        
        float frame_duration = 1.0f / frame_rate;
        if (anim_states[comp_idx].frame_timer >= frame_duration) {
            anim_states[comp_idx].frame_timer = 0.0f;
            
            int rsc_idx = anim_states[comp_idx].resource_index;
            if (rsc_idx >= 0 && rsc_idx < 10) {
                AnimationRsc* rscs = animation_rscs_get();
                int max_frame = rscs[rsc_idx].frame_amount - 1;
                int old_frame = anim_states[comp_idx].current_frame;
                anim_states[comp_idx].current_frame++;
                if (anim_states[comp_idx].current_frame > max_frame) {
                    anim_states[comp_idx].current_frame = 0;  // Loop
                }
                int new_frame = anim_states[comp_idx].current_frame;
            }
        }
    }
}

int animation_resource_get_rsc_index_from_key(EntityKey key){
    int comp_idx = animation_resource_index_get_from_key(key);
    if (comp_idx >= 0 && comp_idx < MAX_ENTITIES) {
        return anim_states[comp_idx].resource_index;
    }
    return -1;
}
