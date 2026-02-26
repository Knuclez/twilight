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

//TRAITS
/* component bitmask constants (same values as before) */
#define IS_DRAWABLE_MASK    	0b00000000000000000000000000000010
#define IS_MOVING_MASK     	0b00000000000000000000000000000100
#define IS_PLAYER_MASK     	0b00000000000000000000000000001000
#define HAS_ANIMATION_MASK 	0b00000000000000000000000000010000
#define IS_DAMAGE_MASK		0b00000000000000000000000000100000
#define HAS_COLIDER_MASK	0b00000000000000000000000001000000

//TYPES
typedef enum {NCC, MOB} CombatType;  //NCC = no combatable character;

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


//STATES
/* animation state kept here because it is part of entity data */
typedef struct {
    int anim_set_index;      /* índice en g_anim_sets */
    int current_frame;       /* frame actual */
    float frame_timer;       /* timer para cambio de frame */
} AnimationState;

/* Direction is a bitmask: bits can be OR-ed together for diagonals.
   DIR_IDLE (0) means no movement. */
typedef int Direction;
#define DIR_IDLE  0
#define DIR_N     0b00000001
#define DIR_S     0b00000010
#define DIR_W     0b00000100
#define DIR_E     0b00001000
#define DIR_NW    (DIR_N | DIR_W)
#define DIR_NE    (DIR_N | DIR_E)
#define DIR_SW    (DIR_S | DIR_W)
#define DIR_SE    (DIR_S | DIR_E)
typedef enum { CHILL, CHASING, ATTACKING, ATTACKED, TREMBLE} CombatState;

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

    CombatType combat_type;
    /* components */
    Position position;
    Size size;
    DirectionVec direction_vec;
    EntityKey target_key;
    PhysicalBounds physical_bounds;
    SpriteSource sprite_source;
    int lifetime;
    int damage;
    int health;
    int combat_state_timer;

    AnimationState animation;
    Direction direction;
    CombatState combat_state;
} Entity;


/* core API */
Entity* entities_get();              /* pointer to the storage array */
int entities_max_index();            /* highest slot ever used */
void entities_list_init();           /* reset all slots to empty */
EntityKey entity_create();           /* allocate a new entity */
void entity_add_bitmask(EntityKey key, int n_bitmask);
void entity_deactivate(Entity *entities, EntityKey key);
void print_bitmask_debug(Entity *entities, EntityKey key);

/* component helpers (formerly separate modules) */
/* setters/getters operate directly on the unified Entity struct */
void entity_set_combat_type(EntityKey key, CombatType combat_type);
CombatType entity_get_combat_type(EntityKey key);

void entity_set_combat_state(EntityKey key, CombatState combate_state);
CombatState entity_get_combat_state(EntityKey key);

void entity_set_combat_state_timer(EntityKey key, int timer);
int entity_get_combat_state_timer(EntityKey key);

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

void entity_set_damage(EntityKey key, int damage);
int entity_get_damage(EntityKey key);

void entity_set_health(EntityKey key, int health);
int entity_get_health(EntityKey key);

void entity_set_animation(EntityKey key, int resource_index);
AnimationState entity_get_animation(EntityKey key);

void entity_set_target(EntityKey key, EntityKey target);
EntityKey entity_get_target(EntityKey key);

#endif
