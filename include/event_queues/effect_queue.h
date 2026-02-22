#ifndef EFFECT_QUEUE_H
#define EFFECT_QUEUE_H

#define EFFECT_QUEUE_SIZE 20

typedef enum {TREMBLE} EffectType;

typedef struct {
    int id;               /* index into entity list */
    int generation;
    EffectType type;
    int affected_entity_index;
    int affected_entity_generation;
    int max_lifetime;
    int current_lifetime;
    int active;
} Effect;

typedef struct {
    Effect queue[EFFECT_QUEUE_SIZE];
    int effect_count;
} EffectQueue;

void effect_queue_init(EffectQueue *queue);
int  effect_queue_add(EffectQueue *queue, Effect effect);
void effect_queue_deactivate(EffectQueue *queue, int index, int generation);
Effect *effect_queue_get_list(EffectQueue *queue);
int  effect_queue_get_count(EffectQueue *queue);

#endif
