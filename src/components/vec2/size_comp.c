// src/components/vec2/size_comp.c
#include <stdio.h>
#include <string.h>
#include "components/size_comp.h"

// ===== SoA STORAGE (Array Denso) =====
Size sizes[MAX_ENTITIES];
int size_count = 0;

// ===== MAPEOS =====
int entity_to_size_index[MAX_ENTITIES];
int entity_size_generation[MAX_ENTITIES];
int size_to_entity_index[MAX_ENTITIES];

// ===== PUBLIC API =====

Size* sizes_get() {
    return sizes;
}

int size_count_get() {
    return size_count;
}

// ⭐ VERSION SEGURA CON GENERATION CHECK
int size_index_get_from_key(EntityKey key) {
    // Validar índice
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }
    
    // ⭐ VALIDAR GENERATION para detectar entidades destruidas
    if (entity_size_generation[key.index] != key.generation) {
        return -1;  // Entidad vieja, componente no existe
    }
    
    int sz_idx = entity_to_size_index[key.index];
    
    if (sz_idx < 0 || sz_idx >= size_count) {
        return -1;
    }
    
    return sz_idx;
}

int size_to_entity_index_get(int soa_index) {
    if (soa_index < 0 || soa_index >= size_count) {
        return -1;
    }
    return size_to_entity_index[soa_index];
}

EntityKey size_get_entity_by_index(int soa_index) {
    EntityKey invalid = {-1, -1, 0};
    
    if (soa_index < 0 || soa_index >= size_count) {
        return invalid;
    }
    
    int entity_idx = size_to_entity_index[soa_index];
    if (entity_idx < 0 || entity_idx >= MAX_ENTITIES) {
        return invalid;
    }
    
    EntityKey *entities_array = entities_get();
    EntityKey result = entities_array[entity_idx];
    
    return result;
}

Size size_get_by_key(EntityKey key) {
    int idx = size_index_get_from_key(key);
    if (idx < 0) {
        return (Size){0, 0};
    }
    return sizes[idx];
}

void size_component_add(EntityKey key, int x, int y) {
    // Validar entidad
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }
    
    // Verificar que no esté ya agregado
    if (entity_size_generation[key.index] == key.generation) {
        printf("Size component already exists for entity %d\n", key.index);
        return;
    }
    
    // Verificar overflow
    if (size_count >= MAX_ENTITIES) {
        printf("Size component list is full!\n");
        return;
    }
    
    // Agregar al final del array denso
    int new_idx = size_count;
    sizes[new_idx].x = x;
    sizes[new_idx].y = y;
    
    // ⭐ Actualizar mapeos bidireccionales
    entity_to_size_index[key.index] = new_idx;
    entity_size_generation[key.index] = key.generation;
    size_to_entity_index[new_idx] = key.index;
    
    size_count++;
}

void size_component_remove(EntityKey key) {
    // Obtener índice con validación
    int idx = size_index_get_from_key(key);
    if (idx < 0) {
        printf("Size component not found or generation mismatch\n");
        return;
    }
    
    // Swap-and-pop: reemplazar con el último
    if (idx < size_count - 1) {
        int last_idx = size_count - 1;
        int last_entity_key_index = size_to_entity_index[last_idx];
        
        // Mover último al lugar a eliminar
        sizes[idx] = sizes[last_idx];
        
        // Actualizar mapeo del último
        entity_to_size_index[last_entity_key_index] = idx;
        size_to_entity_index[idx] = last_entity_key_index;
    }
    
    // Invalidar
    entity_to_size_index[key.index] = -1;
    entity_size_generation[key.index] = -1;
    
    size_count--;
}

int size_component_list_init() {
    size_count = 0;
    
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_size_index[i] = -1;
        entity_size_generation[i] = -1;
        size_to_entity_index[i] = -1;
    }
    
    return 1;
}
