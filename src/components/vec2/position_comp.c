// src/components/vec2/position_comp.c
#include <stdio.h>
#include <string.h>
#include "components/position_comp.h"

// ===== SoA STORAGE (Array Denso) =====
Position positions[MAX_ENTITIES];
int position_count = 0;

// ===== MAPEOS =====
int entity_to_position_index[MAX_ENTITIES];
int entity_position_generation[MAX_ENTITIES];
int position_to_entity_index[MAX_ENTITIES];

// ===== PUBLIC API =====

Position* positions_get() {
    return positions;
}

int position_count_get() {
    return position_count;
}

// ⭐ VERSION SEGURA CON GENERATION CHECK
int position_index_get_from_key(EntityKey key) {
    // Validar índice
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }
    
    // ⭐ VALIDAR GENERATION para detectar entidades destruidas
    if (entity_position_generation[key.index] != key.generation) {
        return -1;  // Entidad vieja, componente no existe
    }
    
    int pos_idx = entity_to_position_index[key.index];
    
    if (pos_idx < 0 || pos_idx >= position_count) {
        return -1;
    }
    
    return pos_idx;
}

int position_to_entity_index_get(int soa_index) {
    if (soa_index < 0 || soa_index >= position_count) {
        return -1;
    }
    return position_to_entity_index[soa_index];
}

EntityKey position_get_entity_by_index(int soa_index) {
    EntityKey invalid = {-1, -1, 0};
    
    if (soa_index < 0 || soa_index >= position_count) {
        return invalid;
    }
    
    int entity_idx = position_to_entity_index[soa_index];
    if (entity_idx < 0 || entity_idx >= MAX_ENTITIES) {
        return invalid;
    }
    
    EntityKey *entities_array = entities_get();
    EntityKey result = entities_array[entity_idx];
    
    return result;
}

Position position_get_by_key(EntityKey key) {
    int idx = position_index_get_from_key(key);
    if (idx < 0) {
        return (Position){0, 0};
    }
    return positions[idx];
}

void position_component_add(EntityKey key, int x, int y) {
    // Validar entidad
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }
    
    // Verificar que no esté ya agregado
    if (entity_position_generation[key.index] == key.generation) {
        printf("Position component already exists for entity %d\n", key.index);
        return;
    }
    
    // Verificar overflow
    if (position_count >= MAX_ENTITIES) {
        printf("Position component list is full!\n");
        return;
    }
    
    // Agregar al final del array denso
    int new_idx = position_count;
    positions[new_idx].x = x;
    positions[new_idx].y = y;
    
    // ⭐ Actualizar mapeos bidireccionales
    entity_to_position_index[key.index] = new_idx;
    entity_position_generation[key.index] = key.generation;
    position_to_entity_index[new_idx] = key.index;
    
    position_count++;
}

void position_component_remove(EntityKey key) {
    // Obtener índice con validación
    int idx = position_index_get_from_key(key);
    if (idx < 0) {
        printf("Position component not found or generation mismatch\n");
        return;
    }
    
    // Swap-and-pop: reemplazar con el último
    if (idx < position_count - 1) {
        int last_idx = position_count - 1;
        int last_entity_key_index = position_to_entity_index[last_idx];
        
        // Mover último al lugar a eliminar
        positions[idx] = positions[last_idx];
        
        // Actualizar mapeo del último
        entity_to_position_index[last_entity_key_index] = idx;
        position_to_entity_index[idx] = last_entity_key_index;
    }
    
    // Invalidar
    entity_to_position_index[key.index] = -1;
    entity_position_generation[key.index] = -1;
    
    position_count--;
}

int position_component_list_init() {
    position_count = 0;
    
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_position_index[i] = -1;
        entity_position_generation[i] = -1;
        position_to_entity_index[i] = -1;
    }
    
    return 1;
}