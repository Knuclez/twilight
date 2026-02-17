#ifndef ENTITIES_H
#define ENTITIES_H

/*
   Central definition for the entity storage.  Instead of keeping
   component data in separate arrays (SoA), every possible component
   is now embedded directly in the entity struct.  A handle type
   (`EntityKey`) is still used to refer to entities from other
   modules; under the hood it is simply an alias for `Entity` so
   existing code that still passes/returns `EntityKey` will continue
   to compile.
*/

#define LIST_SIZE 50
#define BUCKET_SIZE 10
#define MAX_ENTITIES (LIST_SIZE * BUCKET_SIZE)

/* component bitmask constants (same values as before) */
#define IS_DRAWABLE_MASK    	0b00000000000000000000000000000010
#define IS_MOVABLE_MASK     	0b00000000000000000000000000000100
#define IS_PLAYER_MASK     	0b00000000000000000000000000001000
#define HAS_ANIMATION_MASK 	0b00000000000000000000000000010000
#define IS_DAMAGE_MASK		0b00000000000000000000000000100000
#define HAS_COLIDER_MASK	0b00000000000000000000000001000000

/* basic component types previously defined in their own headers */
typedef struct { int x; int y; } Position;
typedef struct { int x; int y; } Size;
typedef struct { int x; int y; } DirectionVec;
typedef struct { int x; int y; int width; int height; } PhysicalBounds;

typedef struct {
    int txtr_indx;
    int x;
    int y;
    int width;
    int height;
} SpriteSource;

/* animation state kept here because it is part of entity data */
typedef struct {
    int resource_index;      /* índice en animation_rscs */
    int current_frame;       /* frame actual (0 a frame_amount-1) */
    float frame_timer;       /* timer para cambio de frame */
} AnimationState;

/* simple enum for direction; kept here for convenience */
typedef enum { IDLE, NW, N, NE, W, E, SW, S, SE } Direction;

typedef struct {
    int index;
    int generation;
}EntityKey;

/* Final entity structure: every field that belonged to a component is
   now a member.  Presence of a component is determined by the
   bitmask field, so no separate `has_` flags are necessary. */
typedef struct Entity {
    EntityKey key;
    int bitmask;

    /* components */
    Position position;
    Size size;
    DirectionVec direction_vec;
    PhysicalBounds physical_bounds;
    SpriteSource sprite_source;
    int lifetime;
    AnimationState animation;
    Direction direction;
} Entity;


/* storage array */
extern Entity entities[MAX_ENTITIES];

/* core API */
Entity* entities_get();              /* pointer to the storage array */
int entities_max_index();            /* highest slot ever used */
void entities_list_init();           /* reset all slots to empty */
EntityKey entity_create();           /* allocate a new entity */
void entity_add_bitmask(EntityKey key, int n_bitmask);

/* component helpers (formerly separate modules) */
/* setters/getters operate directly on the unified Entity struct */
void entity_set_position(EntityKey key, int x, int y);
Position entity_get_position(EntityKey key);

void entity_set_size(EntityKey key, int x, int y);
Size entity_get_size(EntityKey key);

void entity_set_physical_bounds(EntityKey key, int x, int y, int w, int h);
PhysicalBounds entity_get_physical_bounds(EntityKey key);

void entity_set_sprite_source(EntityKey key, int txtr, int x, int y, int w, int h);
SpriteSource entity_get_sprite_source(EntityKey key);

void entity_set_direction_vec(EntityKey key, int x, int y);
DirectionVec entity_get_direction_vec(EntityKey key);

void entity_set_direction(EntityKey key, Direction dir);
Direction entity_get_direction(EntityKey key);

void entity_set_lifetime(EntityKey key, int life);
int entity_get_lifetime(EntityKey key);

void entity_set_animation(EntityKey key, int resource_index);
AnimationState entity_get_animation(EntityKey key);

#endif
