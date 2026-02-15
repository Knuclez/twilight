#include <stdio.h>
#include <string.h>          /* for memset */
#include "entities.h"

/* storage for all entities */
Entity entities[MAX_ENTITIES];
int max_index;

Entity* entities_get(){
    return entities;
}

int entities_max_index(){
    return max_index;
}

EntityKey entity_create(){
    EntityKey result = {0};

    /* find a free slot */
    for (int i = 1; i < MAX_ENTITIES; i++) {
        if (entities[i].key.index == -1) {
            /* reset everything to zero/defaults then set index/generation */
            memset(&entities[i], 0, sizeof(Entity));
            result.index = i;
            result.generation = entities[i].key.generation + 1;
            entities[i].key = result;
            max_index = (i >= max_index) ? (i + 1) : max_index;
            return result;
        }
    }
    /* no space */
    return result;
}

void entity_add_bitmask(EntityKey key, int n_bitmas){
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        return;
    }
    if (entities[key.index].key.generation != key.generation) {
        printf("generation dont match for index %u\n", key.index);
        return;
    }
    entities[key.index].bitmask = n_bitmas;
}


void entities_list_init(){
    max_index = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        /* mark slot as empty */
        entities[i].key.index = -1;
        entities[i].key.generation = 0;
        entities[i].bitmask = 0;
        /* remaining fields already zeroed by static initialization,
           but we clear them just in case. */
        entities[i].position = (Position){0,0};
        entities[i].size = (Size){0,0};
        entities[i].direction_vec = (DirectionVec){0,0};
        entities[i].physical_bounds = (PhysicalBounds){0,0,0,0};
        entities[i].sprite_source = (SpriteSource){0,0,0,0,0};
        entities[i].lifetime = 0;
        entities[i].animation = (AnimationState){0,0,0.0f};
        entities[i].direction = IDLE;
    }
}

/* component accessors ------------------------------------------------------ */

static int valid_key(EntityKey key) {
    return key.index >= 0 && key.index < MAX_ENTITIES &&
           entities[key.index].key.generation == key.generation;
}

void entity_set_position(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    entities[key.index].position.x = x;
    entities[key.index].position.y = y;
    entities[key.index].bitmask |= IS_MOVABLE_MASK;  /* originally used for pos? */
}

Position entity_get_position(EntityKey key) {
    if (!valid_key(key)) return (Position){0,0};
    return entities[key.index].position;
}

void entity_set_size(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    entities[key.index].size.x = x;
    entities[key.index].size.y = y;
    entities[key.index].bitmask |= IS_DRAWABLE_MASK;
}

Size entity_get_size(EntityKey key) {
    if (!valid_key(key)) return (Size){0,0};
    return entities[key.index].size;
}

void entity_set_physical_bounds(EntityKey key, int x, int y, int w, int h) {
    if (!valid_key(key)) return;
    entities[key.index].physical_bounds.x = x;
    entities[key.index].physical_bounds.y = y;
    entities[key.index].physical_bounds.width = w;
    entities[key.index].physical_bounds.height = h;
    /* physical bounds generally accompanies drawable */
    entities[key.index].bitmask |= IS_DRAWABLE_MASK;
}

PhysicalBounds entity_get_physical_bounds(EntityKey key) {
    if (!valid_key(key)) return (PhysicalBounds){0,0,0,0};
    return entities[key.index].physical_bounds;
}

void entity_set_sprite_source(EntityKey key, int txtr, int x, int y, int w, int h) {
    if (!valid_key(key)) return;
    SpriteSource *s = &entities[key.index].sprite_source;
    s->txtr_indx = txtr;
    s->x = x; s->y = y; s->width = w; s->height = h;
    entities[key.index].bitmask |= IS_DRAWABLE_MASK;
}

SpriteSource entity_get_sprite_source(EntityKey key) {
    if (!valid_key(key)) return (SpriteSource){0,0,0,0,0};
    return entities[key.index].sprite_source;
}

void entity_set_direction_vec(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    entities[key.index].direction_vec.x = x;
    entities[key.index].direction_vec.y = y;
    entities[key.index].bitmask |= IS_MOVABLE_MASK;
}

DirectionVec entity_get_direction_vec(EntityKey key) {
    if (!valid_key(key)) return (DirectionVec){0,0};
    return entities[key.index].direction_vec;
}

void entity_set_direction(EntityKey key, Direction dir) {
    if (!valid_key(key)) return;
    entities[key.index].direction = dir;
}

Direction entity_get_direction(EntityKey key) {
    if (!valid_key(key)) return IDLE;
    return entities[key.index].direction;
}

void entity_set_lifetime(EntityKey key, int life) {
    if (!valid_key(key)) return;
    entities[key.index].lifetime = life;
}

int entity_get_lifetime(EntityKey key) {
    if (!valid_key(key)) return 0;
    return entities[key.index].lifetime;
}

void entity_set_animation(EntityKey key, int resource_index) {
    if (!valid_key(key)) return;
    entities[key.index].animation.resource_index = resource_index;
    entities[key.index].animation.current_frame = 0;
    entities[key.index].animation.frame_timer = 0.0f;
    entities[key.index].bitmask |= HAS_ANIMATION_MASK;
}

AnimationState entity_get_animation(EntityKey key) {
    if (!valid_key(key)) return (AnimationState){0,0,0.0f};
    return entities[key.index].animation;
}

