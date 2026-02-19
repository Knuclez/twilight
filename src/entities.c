#include <stdio.h>
#include <string.h>          /* for memset */
#include "entities.h"
#include "game_state.h"

Entity* entities_get(){
    return get_game_state_p()->entities;
}

int entities_max_index(){
    return get_game_state_p()->max_index;
}

EntityKey entity_create(){
    EntityKey result = {0};

    GameState *gs = get_game_state_p();
    /* find a free slot */
    for (int i = 1; i < MAX_ENTITIES; i++) {
        if (gs->entities[i].key.index == -1) {
            /* reset everything to zero/defaults then set index/generation */
            memset(&gs->entities[i], 0, sizeof(Entity));
            result.index = i;
            result.generation = gs->entities[i].key.generation + 1;
            gs->entities[i].key = result;
            gs->max_index = (i >= gs->max_index) ? (i + 1) : gs->max_index;
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
    GameState *gs = get_game_state_p();
    if (gs->entities[key.index].key.generation != key.generation) {
        printf("generation dont match for index %u\n", key.index);
        return;
    }
    gs->entities[key.index].bitmask = n_bitmas;
}


void entities_list_init(){
    GameState *gs = get_game_state_p();
    gs->max_index = 0;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        /* mark slot as empty */
        gs->entities[i].key.index = -1;
        gs->entities[i].key.generation = 0;
        gs->entities[i].bitmask = 0;
        gs->entities[i].position = (Position){0,0};
        gs->entities[i].size = (Size){0,0};
        gs->entities[i].direction_vec = (DirectionVec){0,0};
        gs->entities[i].physical_bounds = (PhysicalBounds){0,0,0,0};
        gs->entities[i].sprite_source = (SpriteSource){0,0,0,0,0};
        gs->entities[i].lifetime = 0;
        gs->entities[i].animation = (AnimationState){0,0,0.0f};
        gs->entities[i].direction = IDLE;
    }
}

void entity_deactivate(Entity *ents, EntityKey key){
    GameState *gs = get_game_state_p();
    if(gs->entities[key.index].key.generation == key.generation){
        gs->entities[key.index].bitmask = 0;
        gs->entities[key.index].key.index = 0;
    }
}

/* component accessors ------------------------------------------------------ */

static int valid_key(EntityKey key) {
    return key.index >= 0 && key.index < MAX_ENTITIES &&
           get_game_state_p()->entities[key.index].key.generation == key.generation;
}

static Entity* ep(EntityKey key) {
    return &get_game_state_p()->entities[key.index];
}

void entity_set_position(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    ep(key)->position.x = x;
    ep(key)->position.y = y;
    ep(key)->bitmask |= IS_MOVABLE_MASK;
}

Position entity_get_position(EntityKey key) {
    if (!valid_key(key)) return (Position){0,0};
    return ep(key)->position;
}

void entity_set_size(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    ep(key)->size.x = x;
    ep(key)->size.y = y;
    ep(key)->bitmask |= IS_DRAWABLE_MASK;
}

Size entity_get_size(EntityKey key) {
    if (!valid_key(key)) return (Size){0,0};
    return ep(key)->size;
}

void entity_set_physical_bounds(EntityKey key, int x, int y, int w, int h) {
    if (!valid_key(key)) return;
    ep(key)->physical_bounds.x = x;
    ep(key)->physical_bounds.y = y;
    ep(key)->physical_bounds.width = w;
    ep(key)->physical_bounds.height = h;
    ep(key)->bitmask |= IS_DRAWABLE_MASK;
}

PhysicalBounds entity_get_physical_bounds(EntityKey key) {
    if (!valid_key(key)) return (PhysicalBounds){0,0,0,0};
    return ep(key)->physical_bounds;
}

void entity_set_sprite_source(EntityKey key, int txtr, int x, int y, int w, int h) {
    if (!valid_key(key)) return;
    SpriteSource *s = &ep(key)->sprite_source;
    s->txtr_indx = txtr;
    s->x = x; s->y = y; s->width = w; s->height = h;
    ep(key)->bitmask |= IS_DRAWABLE_MASK;
}

SpriteSource entity_get_sprite_source(EntityKey key) {
    if (!valid_key(key)) return (SpriteSource){0,0,0,0,0};
    return ep(key)->sprite_source;
}

void entity_set_direction_vec(EntityKey key, int x, int y) {
    if (!valid_key(key)) return;
    ep(key)->direction_vec.x = x;
    ep(key)->direction_vec.y = y;
    ep(key)->bitmask |= IS_MOVABLE_MASK;
}

DirectionVec entity_get_direction_vec(EntityKey key) {
    if (!valid_key(key)) return (DirectionVec){0,0};
    return ep(key)->direction_vec;
}

void entity_set_direction(EntityKey key, Direction dir) {
    if (!valid_key(key)) return;
    ep(key)->direction = dir;
}

Direction entity_get_direction(EntityKey key) {
    if (!valid_key(key)) return IDLE;
    return ep(key)->direction;
}

void entity_set_lifetime(EntityKey key, int life) {
    if (!valid_key(key)) return;
    ep(key)->lifetime = life;
}

int entity_get_lifetime(EntityKey key) {
    if (!valid_key(key)) return 0;
    return ep(key)->lifetime;
}

void entity_set_damage(EntityKey key, int damage) {
    if (!valid_key(key)) return;
    ep(key)->damage = damage;
}

int entity_get_damage(EntityKey key) {
    if (!valid_key(key)) return 0;
    return ep(key)->damage;
}

void entity_set_health(EntityKey key, int health) {
    if (!valid_key(key)) return;
    ep(key)->health = health;
}

int entity_get_health(EntityKey key) {
    if (!valid_key(key)) return 0;
    return ep(key)->health;
}

void entity_set_animation(EntityKey key, int resource_index) {
    if (!valid_key(key)) return;
    ep(key)->animation.resource_index = resource_index;
    ep(key)->animation.current_frame = 0;
    ep(key)->animation.frame_timer = 0.0f;
    ep(key)->bitmask |= HAS_ANIMATION_MASK;
}

AnimationState entity_get_animation(EntityKey key) {
    if (!valid_key(key)) return (AnimationState){0,0,0.0f};
    return ep(key)->animation;
}

