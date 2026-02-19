#include <stdio.h> 
#include <string.h>
#include "event_queues/collision_queue.h"

void collision_queue_init(CollisionQueue* queue) {
    if (queue == NULL) return;
    
    memset(queue->collisions, 0, sizeof(queue->collisions));
    queue->next_slot = 0;
}

int collision_queue_add(CollisionQueue* queue, EntityKey entity1, EntityKey entity2) {
    if (queue == NULL) return -1;
    if (queue->next_slot >= COLLISION_QUEUE_SIZE) return -1; // Queue is full
    
    queue->collisions[queue->next_slot].entity1 = entity1;
    queue->collisions[queue->next_slot].entity2 = entity2;
    queue->next_slot++;
    
    return queue->next_slot - 1; // Return index of added collision
}

void collision_queue_clear(CollisionQueue* queue) {
    if (queue == NULL) return;
    
    memset(queue->collisions, 0, sizeof(queue->collisions));
    queue->next_slot = 0;
}

Collision* collision_queue_get_list(CollisionQueue* queue) {
    if (queue == NULL) return NULL;
    
    return queue->collisions;
}

int collision_queue_get_count(CollisionQueue* queue) {
    if (queue == NULL) return 0;
    
    return queue->next_slot;
}
