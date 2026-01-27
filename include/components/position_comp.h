// include/components/position_comp.h
#ifndef POSITION_COMP_H
#define POSITION_COMP_H

#include "entities.h"

typedef struct {
    int x;
    int y;
} Position;

// ===== SoA STORAGE (Array Denso) =====
extern Position positions[MAX_ENTITIES];
extern int position_count;

// ===== MAPEO BIDIRECCIONAL =====
// Sparse → Dense: EntityKey.index → índice en positions[]
extern int entity_to_position_index[MAX_ENTITIES];
extern int entity_position_generation[MAX_ENTITIES];

// Dense → Sparse: índice en positions[] → EntityKey.index
extern int position_to_entity_index[MAX_ENTITIES];

// ===== API =====
Position* positions_get();
int position_count_get();
int position_index_get_from_key(EntityKey key);
void position_component_add(EntityKey key, int x, int y);
void position_component_remove(EntityKey key);
int position_component_list_init();

// ===== HELPERS =====
Position position_get_by_key(EntityKey key);
EntityKey position_get_entity_by_index(int soa_index);
int position_to_entity_index_get(int soa_index);

#endif