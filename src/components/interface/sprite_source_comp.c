// src/components/interface/sprite_source_comp.c
#include <stdio.h>
#include <string.h>
#include "components/sprite_source_comp.h"

// ===== SoA STORAGE (Array Denso) =====
SpriteSource sprite_sources[MAX_ENTITIES];
int sprite_source_count = 0;

// ===== MAPEOS =====
int entity_to_sprite_source_index[MAX_ENTITIES];
int entity_sprite_source_generation[MAX_ENTITIES];
int sprite_source_to_entity_index[MAX_ENTITIES];

// ===== PUBLIC API =====

SpriteSource* sprite_sources_get() {
    return sprite_sources;
}

int sprite_source_count_get() {
    return sprite_source_count;
}

int sprite_source_index_get_from_key(EntityKey key) {
    // Validar índice
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return -1;
    }
    
    // Validar generation
    if (entity_sprite_source_generation[key.index] != key.generation) {
        return -1;
    }
    
    int sprite_src_idx = entity_to_sprite_source_index[key.index];
    
    if (sprite_src_idx < 0 || sprite_src_idx >= sprite_source_count) {
        return -1;
    }
    
    return sprite_src_idx;
}

int sprite_source_to_entity_index_get(int soa_index) {
    if (soa_index < 0 || soa_index >= sprite_source_count) {
        return -1;
    }
    return sprite_source_to_entity_index[soa_index];
}

SpriteSource sprite_source_get_by_key(EntityKey key) {
    int idx = sprite_source_index_get_from_key(key);
    if (idx < 0) {
        return (SpriteSource){0, 0, 0, 0};
    }
    return sprite_sources[idx];
}

void sprite_source_component_add(EntityKey key, int txtr_src, int x, int y, int width, int height) {
    // Validar entidad
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        printf("Invalid entity index: %d\n", key.index);
        return;
    }
    
    // Verificar que no esté ya agregado
    if (entity_sprite_source_generation[key.index] == key.generation) {
        printf("Sprite source component already exists for entity %d\n", key.index);
        return;
    }
    
    // Verificar overflow
    if (sprite_source_count >= MAX_ENTITIES) {
        printf("Sprite source component list is full!\n");
        return;
    }
    
    // Agregar al final del array denso
    int new_idx = sprite_source_count;
    sprite_sources[new_idx].txtr_indx = txtr_src;
    sprite_sources[new_idx].x = x;
    sprite_sources[new_idx].y = y;
    sprite_sources[new_idx].width = width;
    sprite_sources[new_idx].height = height;
    
    // Actualizar mapeos bidireccionales
    entity_to_sprite_source_index[key.index] = new_idx;
    entity_sprite_source_generation[key.index] = key.generation;
    sprite_source_to_entity_index[new_idx] = key.index;
    
    sprite_source_count++;
}

void sprite_source_component_remove(EntityKey key) {
    // Obtener índice con validación
    int idx = sprite_source_index_get_from_key(key);
    if (idx < 0) {
        printf("Sprite source component not found or generation mismatch\n");
        return;
    }
    
    // Swap-and-pop
    if (idx < sprite_source_count - 1) {
        int last_idx = sprite_source_count - 1;
        int last_entity_key_index = sprite_source_to_entity_index[last_idx];
        
        // Mover último al lugar a eliminar
        sprite_sources[idx] = sprite_sources[last_idx];
        
        // Actualizar mapeo del último
        entity_to_sprite_source_index[last_entity_key_index] = idx;
        sprite_source_to_entity_index[idx] = last_entity_key_index;
    }
    
    // Invalidar
    entity_to_sprite_source_index[key.index] = -1;
    entity_sprite_source_generation[key.index] = -1;
    
    sprite_source_count--;
}

int sprite_source_component_list_init() {
    sprite_source_count = 0;
    
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_to_sprite_source_index[i] = -1;
        entity_sprite_source_generation[i] = -1;
        sprite_source_to_entity_index[i] = -1;
    }
    
    return 1;
}
