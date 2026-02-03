#include <stdio.h>
#include <string.h>
#include "components/direction_vec_comp.h"

// ===== SoA STORAGE (Array Denso) =====
DirectionVec direction_vecs[MAX_ENTITIES];
int direction_vec_count = 0;

// ===== MAPEOS =====
int entity_to_direction_vec_index[MAX_ENTITIES];
int entity_direction_vec_generation[MAX_ENTITIES];
int direction_vec_to_entity_index[MAX_ENTITIES];

// ===== PUBLIC API =====

DirectionVec* direction_vecs_get() {
    return direction_vecs;
}

int direction_vec_count_get() {
    return direction_vec_count;
}

int direction_vec_index_get_from_key(EntityKey key) {
    // Validar índice
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }

    if (entity_direction_vec_generation[key.index] != key.generation) {
        return -1;
    }

    int idx = entity_to_direction_vec_index[key.index];
    if (idx < 0 || idx >= direction_vec_count) {
        return -1;
    }

    return idx;
}

int direction_vec_to_entity_index_get(int soa_index) {
    if (soa_index < 0 || soa_index >= direction_vec_count) {
        return -1;
    }
    return direction_vec_to_entity_index[soa_index];
}

EntityKey direction_vec_get_entity_by_index(int soa_index) {
    EntityKey invalid = {-1, -1, 0};

    if (soa_index < 0 || soa_index >= direction_vec_count) {
        return invalid;
    }

    int entity_idx = direction_vec_to_entity_index[soa_index];
    if (entity_idx < 0 || entity_idx >= MAX_ENTITIES) {
        return invalid;
    }

    EntityKey *entities_array = entities_get();
    EntityKey result = entities_array[entity_idx];

    return result;
}

DirectionVec direction_vec_get_by_key(EntityKey key) {
    int idx = direction_vec_index_get_from_key(key);
    if (idx < 0) {
        return (DirectionVec){0, 0};
    }
    return direction_vecs[idx];
}

void direction_vec_component_add(EntityKey key, int x, int y) {
    // Validar entidad
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }

    // Verificar que no esté ya agregado
    if (entity_direction_vec_generation[key.index] == key.generation) {
        printf("DirectionVec component already exists for entity %d\n", key.index);
        return;
    }

    // Verificar overflow
    if (direction_vec_count >= MAX_ENTITIES) {
        printf("DirectionVec component list is full!\n");
        return;
    }

    // Agregar al final del array denso
    int new_idx = direction_vec_count;
    direction_vecs[new_idx].x = x;
    direction_vecs[new_idx].y = y;

    // Actualizar mapeos bidireccionales
    entity_to_direction_vec_index[key.index] = new_idx;
    entity_direction_vec_generation[key.index] = key.generation;
    direction_vec_to_entity_index[new_idx] = key.index;

    direction_vec_count++;
}

void direction_vec_component_remove(EntityKey key) {
    int idx = direction_vec_index_get_from_key(key);
    if (idx < 0) {
        printf("DirectionVec component not found or generation mismatch\n");
        return;
    }

    // Swap-and-pop: reemplazar con el último
    if (idx < direction_vec_count - 1) {
        int last_idx = direction_vec_count - 1;
        int last_entity_key_index = direction_vec_to_entity_index[last_idx];

        // Mover último al lugar a eliminar
        direction_vecs[idx] = direction_vecs[last_idx];

        // Actualizar mapeo del último
        entity_to_direction_vec_index[last_entity_key_index] = idx;
        direction_vec_to_entity_index[idx] = last_entity_key_index;
    }

    // Invalidar
    entity_to_direction_vec_index[key.index] = -1;
    entity_direction_vec_generation[key.index] = -1;

    direction_vec_count--;
}

int direction_vec_component_list_init() {
    direction_vec_count = 0;

    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_direction_vec_index[i] = -1;
        entity_direction_vec_generation[i] = -1;
        direction_vec_to_entity_index[i] = -1;

        // Inicializar valores a 0,0 por seguridad
        direction_vecs[i].x = 0;
        direction_vecs[i].y = 0;
    }

    return 1;
}
