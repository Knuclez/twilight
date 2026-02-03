// include/components/size_comp.h
#ifndef SIZE_COMP_H
#define SIZE_COMP_H

#include "entities.h"

typedef struct {
    int x;
    int y;
} Size;

// ===== SoA STORAGE (Array Denso) =====
extern Size sizes[MAX_ENTITIES];
extern int size_count;

// ===== MAPEO BIDIRECCIONAL =====
// Sparse → Dense: EntityKey.index → índice en sizes[]
extern int entity_to_size_index[MAX_ENTITIES];
extern int entity_size_generation[MAX_ENTITIES];

// Dense → Sparse: índice en sizes[] → EntityKey.index
extern int size_to_entity_index[MAX_ENTITIES];

// ===== API =====
Size* sizes_get();
int size_count_get();
int size_index_get_from_key(EntityKey key);
void size_component_add(EntityKey key, int x, int y);
void size_component_remove(EntityKey key);
int size_component_list_init();

// ===== HELPERS =====
Size size_get_by_key(EntityKey key);
EntityKey size_get_entity_by_index(int soa_index);
int size_to_entity_index_get(int soa_index);

#endif
