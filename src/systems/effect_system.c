#include <stdio.h>
#include "systems/effect_system.h"
#include "event_queues/effect_queue.h"
#include "entities.h"
#include "game_state.h"

/*
 * effect_system_tick
 *
 * Advances every active effect in the queue by one tick.
 * Effects that have reached their max_lifetime cause the
 * corresponding entity to be deactivated before being removed
 * from the queue.
 */
void effect_system_tick(GameState *gs) {
    if (gs == NULL) return;

    EffectQueue *eq = &gs->effect_queue;
    Entity *entities = &gs->entities;
    int count = effect_queue_get_count(eq);

    for (int i = 0; i < count; i++) {
        Effect *e = &eq->queue[i];
        if (!e->active) continue;

        if (e->type == TREMBLE) {
	    int affected_entity_index = e->affected_entity_index;
	    int affected_entity_generation = e->affected_entity_generation;
	    if (e->current_lifetime * 2 == e->max_lifetime){
		if(entities[affected_entity_index].key.generation == affected_entity_generation){
		    printf("temblaro grr %u\n", affected_entity_index);
		}
	    }
        }

        e->current_lifetime++;

        if (e->current_lifetime >= e->max_lifetime) {
            printf("[effect_system] effect %u expired, entity deactivated\n", e->id);
            effect_queue_deactivate(eq, i, e->generation);
        }
    }
}
