// src/components/lifetime_comp.c
#include <stdio.h>
#include "components/lifetime_comp.h"
#include "entities.h" // for EntityKey and MAX_ENTITIES

// ===== SoA STORAGE (Array Denso) =====
int lifetimes[MAX_ENTITIES];
int lifetime_count = 0;

// ===== BIDI MAPPINGS =====
int entity_to_lifetime_index[MAX_ENTITIES];
int entity_lifetime_generation[MAX_ENTITIES];
int lifetime_to_entity_index[MAX_ENTITIES];

// ===== API =====

int* lifetimes_get() {
    return lifetimes;
}

int lifetimes_amount_get() {
    return lifetime_count;
}

int* lifetimes_key_indexes_get() {
    return lifetime_to_entity_index; // dense->sparse mapping gives entity indexes
}

int* lifetimes_key_generations_get() {
    return entity_lifetime_generation; // sparse generational table
}

int lifetime_index_get_from_key(EntityKey key) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }
    if (entity_lifetime_generation[key.index] != key.generation) {
        return -1;
    }
    int idx = entity_to_lifetime_index[key.index];
    if (idx < 0 || idx >= lifetime_count) {
        return -1;
    }
    return idx;
}

void lifetime_component_add(EntityKey key, int life) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }
    if (entity_lifetime_generation[key.index] == key.generation) {
        printf("Lifetime component already exists for entity %d\n", key.index);
        return;
    }
    if (lifetime_count >= MAX_ENTITIES) {
        printf("Lifetime component list is full!\n");
        return;
    }
    int new_idx = lifetime_count;
    lifetimes[new_idx] = life;
    entity_to_lifetime_index[key.index] = new_idx;
    entity_lifetime_generation[key.index] = key.generation;
    lifetime_to_entity_index[new_idx] = key.index;
    lifetime_count++;
}

void lifetime_component_remove(EntityKey key) {
    int idx = lifetime_index_get_from_key(key);
    if (idx < 0) {
        printf("Lifetime component not found or generation mismatch\n");
        return;
    }
    if (idx < lifetime_count - 1) {
        int last_idx = lifetime_count - 1;
        int last_entity_idx = lifetime_to_entity_index[last_idx];
        lifetimes[idx] = lifetimes[last_idx];
        entity_to_lifetime_index[last_entity_idx] = idx;
        lifetime_to_entity_index[idx] = last_entity_idx;
    }
    entity_to_lifetime_index[key.index] = -1;
    entity_lifetime_generation[key.index] = -1;
    lifetime_count--;
}

int lifetime_component_list_init() {
    lifetime_count = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_lifetime_index[i] = -1;
        entity_lifetime_generation[i] = -1;
        lifetime_to_entity_index[i] = -1;
    }
    return 1;
}

// ===== HELPERS =====
EntityKey lifetime_get_entity_by_index(int soa_index) {
    EntityKey invalid = {-1, -1, 0};
    if (soa_index < 0 || soa_index >= lifetime_count) {
        return invalid;
    }
    int entity_idx = lifetime_to_entity_index[soa_index];
    if (entity_idx < 0 || entity_idx >= MAX_ENTITIES) {
        return invalid;
    }
    EntityKey *entities_array = entities_get();
    return entities_array[entity_idx];
}
