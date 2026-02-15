// include/components/lifetime_comp.h
#ifndef LIFETIME_COMP_H
#define LIFETIME_COMP_H

#include "entities.h"

// ===== SoA STORAGE (Array Denso) =====
extern int lifetimes[MAX_ENTITIES];
extern int lifetime_count;

// ===== BIDI MAPPINGS =====
// Sparse → Dense: EntityKey.index → índice en lifetimes[]
extern int entity_to_lifetime_index[MAX_ENTITIES];
extern int entity_lifetime_generation[MAX_ENTITIES];

// Dense → Sparse: índice en lifetimes[] → EntityKey.index
extern int lifetime_to_entity_index[MAX_ENTITIES];

// ===== API =====
int* lifetimes_get();
int lifetimes_amount_get();
int* lifetimes_key_indexes_get();
int* lifetimes_key_generations_get();

int lifetime_index_get_from_key(EntityKey key);
void lifetime_component_add(EntityKey key, int life);
void lifetime_component_remove(EntityKey key);
int lifetime_component_list_init();

// ===== HELPERS =====
EntityKey lifetime_get_entity_by_index(int soa_index);

#endif
