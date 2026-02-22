#include <stdio.h>
#include <string.h>
#include "event_queues/effect_queue.h"

void effect_queue_init(EffectQueue *queue) {
    if (queue == NULL) return;

    memset(queue->queue, 0, sizeof(queue->queue));
    queue->effect_count = 0;
}

int effect_queue_add(EffectQueue *queue, Effect effect) {
    if (queue == NULL) return -1;

    /* Find the first free slot (id == 0 means deactivated / never used) */
    int slot = -1;
    for (int i = 0; i < EFFECT_QUEUE_SIZE; i++) {
        if (queue->queue[i].id == 0 && queue->queue[i].active == 0) {
            slot = i;
            break;
        }
    }
    if (slot == -1) return -1; /* queue is completely full */

    effect.current_lifetime = 0;
    effect.active           = 1;
    effect.id = slot;
    effect.generation = queue->queue[slot].generation + 1;
    queue->queue[slot] = effect;

    /* Only advance the high-water mark when we used a brand-new slot */
    if (slot >= queue->effect_count) {
        queue->effect_count = slot + 1;
    }
    return slot;
}

/* Deactivate by generational index to avoid stale references */
void effect_queue_deactivate(EffectQueue *queue, int index, int generation) {
    if (queue == NULL) return;
    /* Guard against the full array size, not effect_count, because slots
       are no longer compacted and can live anywhere in [0, EFFECT_QUEUE_SIZE). */
    if (index < 0 || index >= EFFECT_QUEUE_SIZE) return;

    Effect *e = &queue->queue[index];
    if (e->generation != generation) return; /* stale reference */

    e->active = 0;
    e->id     = 0; /* mark as free so effect_queue_add can reclaim this slot */
}

Effect *effect_queue_get_list(EffectQueue *queue) {
    if (queue == NULL) return NULL;
    return queue->queue;
}

int effect_queue_get_count(EffectQueue *queue) {
    if (queue == NULL) return 0;
    return queue->effect_count;
}
