#ifndef ENTITIES_H
#define ENTITIES_H

#define LIST_SIZE 50
#define BUCKET_SIZE 10
#define MAX_ENTITIES (LIST_SIZE*BUCKET_SIZE)

#define IS_DRAWABLE_MASK 	0b00000000000000000000000000000010
#define IS_MOVABLE_MASK 	0b00000000000000000000000000000100
#define IS_PLAYER_MASK	 	0b00000000000000000000000000001000
#define HAS_ANIMATION_MASK 	0b00000000000000000000000000010000

typedef struct {
    int index;
    int generation;
    int bitmask;
} EntityKey;

EntityKey* entities_get();
int entities_max_index();
void entities_list_init();
EntityKey entity_create();
void entity_add_bitmask();
#endif
