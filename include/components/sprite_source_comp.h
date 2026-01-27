// include/components/sprite_source_comp.h
#ifndef SPRITE_SOURCE_COMP_H
#define SPRITE_SOURCE_COMP_H

#include "entities.h"

typedef struct {
    int x;
    int y;
    int width;
    int height;
} SpriteSource;

// ===== SoA STORAGE (Array Denso) =====
extern SpriteSource sprite_sources[MAX_ENTITIES];
extern int sprite_source_count;

// ===== MAPEO BIDIRECCIONAL =====
extern int entity_to_sprite_source_index[MAX_ENTITIES];
extern int entity_sprite_source_generation[MAX_ENTITIES];
extern int sprite_source_to_entity_index[MAX_ENTITIES];

// ===== API =====
SpriteSource* sprite_sources_get();
int sprite_source_count_get();
int sprite_source_index_get_from_key(EntityKey key);
void sprite_source_component_add(EntityKey key, int x, int y, int width, int height);
void sprite_source_component_remove(EntityKey key);
int sprite_source_component_list_init();

// ===== HELPERS =====
SpriteSource sprite_source_get_by_key(EntityKey key);
int sprite_source_to_entity_index_get(int soa_index);

#endif
