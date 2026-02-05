// src/components/vec2/physical_bounds_comp.c
#include <stdio.h>
#include <string.h>
#include "components/physical_bounds_comp.h"

// ===== SoA STORAGE (Array Denso) =====
PhysicalBounds physical_bounds[MAX_ENTITIES];
int physical_bounds_count = 0;

// ===== MAPEOS =====
int entity_to_physical_bounds_index[MAX_ENTITIES];
int entity_physical_bounds_generation[MAX_ENTITIES];
int physical_bounds_to_entity_index[MAX_ENTITIES];

// ===== PUBLIC API =====

PhysicalBounds* physical_bounds_get() {
    return physical_bounds;
}

int physical_bounds_count_get() {
    return physical_bounds_count;
}

int physical_bounds_index_get_from_key(EntityKey key) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }
    if (entity_physical_bounds_generation[key.index] != key.generation) {
        return -1;
    }
    int idx = entity_to_physical_bounds_index[key.index];
    if (idx < 0 || idx >= physical_bounds_count) return -1;
    return idx;
}

int physical_bounds_to_entity_index_get(int soa_index) {
    if (soa_index < 0 || soa_index >= physical_bounds_count) return -1;
    return physical_bounds_to_entity_index[soa_index];
}

EntityKey physical_bounds_get_entity_by_index(int soa_index) {
    EntityKey invalid = {-1, -1, 0};
    if (soa_index < 0 || soa_index >= physical_bounds_count) return invalid;
    int entity_idx = physical_bounds_to_entity_index[soa_index];
    if (entity_idx < 0 || entity_idx >= MAX_ENTITIES) return invalid;
    EntityKey *entities_array = entities_get();
    return entities_array[entity_idx];
}

PhysicalBounds physical_bounds_get_by_key(EntityKey key) {
    int idx = physical_bounds_index_get_from_key(key);
    if (idx < 0) return (PhysicalBounds){0,0,0,0};
    return physical_bounds[idx];
}

void physical_bounds_component_add(EntityKey key, int x, int y, int width, int height) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }
    if (entity_physical_bounds_generation[key.index] == key.generation) {
        printf("PhysicalBounds component already exists for entity %d\n", key.index);
        return;
    }
    if (physical_bounds_count >= MAX_ENTITIES) {
        printf("PhysicalBounds component list is full!\n");
        return;
    }
    int new_idx = physical_bounds_count;
    physical_bounds[new_idx].x = x;
    physical_bounds[new_idx].y = y;
    physical_bounds[new_idx].width = width;
    physical_bounds[new_idx].height = height;

    entity_to_physical_bounds_index[key.index] = new_idx;
    entity_physical_bounds_generation[key.index] = key.generation;
    physical_bounds_to_entity_index[new_idx] = key.index;

    physical_bounds_count++;
}

void physical_bounds_component_remove(EntityKey key) {
    int idx = physical_bounds_index_get_from_key(key);
    if (idx < 0) {
        printf("PhysicalBounds component not found or generation mismatch\n");
        return;
    }
    if (idx < physical_bounds_count - 1) {
        int last_idx = physical_bounds_count - 1;
        int last_entity_key_index = physical_bounds_to_entity_index[last_idx];
        physical_bounds[idx] = physical_bounds[last_idx];
        entity_to_physical_bounds_index[last_entity_key_index] = idx;
        physical_bounds_to_entity_index[idx] = last_entity_key_index;
    }
    entity_to_physical_bounds_index[key.index] = -1;
    entity_physical_bounds_generation[key.index] = -1;
    physical_bounds_count--;
}

int physical_bounds_component_list_init() {
    physical_bounds_count = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_physical_bounds_index[i] = -1;
        entity_physical_bounds_generation[i] = -1;
        physical_bounds_to_entity_index[i] = -1;
    }
    return 1;
}
