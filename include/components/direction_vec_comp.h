#ifndef DIRECTION_VEC_COMP_H
#define DIRECTION_VEC_COMP_H

#include "entities.h"

typedef struct {
    int x;
    int y;
} DirectionVec;

// ===== SoA STORAGE (Array Denso) =====
extern DirectionVec direction_vecs[MAX_ENTITIES];
extern int direction_vec_count;

// ===== MAPEO BIDIRECCIONAL =====
extern int entity_to_direction_vec_index[MAX_ENTITIES];
extern int entity_direction_vec_generation[MAX_ENTITIES];

// Dense → Sparse
extern int direction_vec_to_entity_index[MAX_ENTITIES];

// ===== API =====
DirectionVec* direction_vecs_get();
int direction_vec_count_get();
int direction_vec_index_get_from_key(EntityKey key);
void direction_vec_component_add(EntityKey key, int x, int y);
void direction_vec_component_remove(EntityKey key);
int direction_vec_component_list_init();

// ===== HELPERS =====
DirectionVec direction_vec_get_by_key(EntityKey key);
EntityKey direction_vec_get_entity_by_index(int soa_index);
int direction_vec_to_entity_index_get(int soa_index);

#endif
