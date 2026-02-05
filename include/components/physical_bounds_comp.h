// include/components/physical_bounds_comp.h
#ifndef PHYSICAL_BOUNDS_COMP_H
#define PHYSICAL_BOUNDS_COMP_H

#include "entities.h"

typedef struct {
    int x;
    int y;
    int width;
    int height;
} PhysicalBounds;

// ===== SoA STORAGE (Array Denso) =====
extern PhysicalBounds physical_bounds[MAX_ENTITIES];
extern int physical_bounds_count;

// ===== MAPEO BIDIRECCIONAL =====
extern int entity_to_physical_bounds_index[MAX_ENTITIES];
extern int entity_physical_bounds_generation[MAX_ENTITIES];
extern int physical_bounds_to_entity_index[MAX_ENTITIES];

// ===== API =====
PhysicalBounds* physical_bounds_get();
int physical_bounds_count_get();
int physical_bounds_index_get_from_key(EntityKey key);
void physical_bounds_component_add(EntityKey key, int x, int y, int width, int height);
void physical_bounds_component_remove(EntityKey key);
int physical_bounds_component_list_init();

// ===== HELPERS =====
PhysicalBounds physical_bounds_get_by_key(EntityKey key);
EntityKey physical_bounds_get_entity_by_index(int soa_index);
int physical_bounds_to_entity_index_get(int soa_index);

#endif
