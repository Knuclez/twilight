#ifndef COLLISION_QUEUE_H
#define COLLISION_QUEUE_H

#include "entities.h"

#define COLLISION_QUEUE_SIZE 20

typedef struct {
    EntityKey entity1;
    EntityKey entity2;
    EntityKey causal_entity; 
} Collision;

typedef struct {
    Collision collisions[COLLISION_QUEUE_SIZE];
    int next_slot;
} CollisionQueue;

// Function declarations
void collision_queue_init(CollisionQueue* queue);
int collision_queue_add(CollisionQueue* queue, EntityKey entity1, EntityKey entity2, EntityKey causal_entity);
void collision_queue_clear(CollisionQueue* queue);
Collision* collision_queue_get_list(CollisionQueue* queue);
int collision_queue_get_count(CollisionQueue* queue);

#endif
