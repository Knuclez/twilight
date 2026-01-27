// include/components/entity_bitmasks.h
#ifndef ENTITY_BITMASKS_H
#define ENTITY_BITMASKS_H

#include "entities.h"

// UN SOLO ARRAY: EntityKey.index → bitmask actual
extern int entity_bitmasks[MAX_ENTITIES];

int entity_get_bitmask(EntityKey key);
void entity_set_bitmask(EntityKey key, int bitmask);
int entity_bitmasks_init();

#endif
