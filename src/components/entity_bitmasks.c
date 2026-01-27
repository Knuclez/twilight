// src/components/entity_bitmasks.c
#include <stdio.h>
#include "components/entity_bitmasks.h"

int entity_bitmasks[MAX_ENTITIES];

int entity_get_bitmask(EntityKey key) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        return 0;
    }
    return entity_bitmasks[key.index];
}

void entity_set_bitmask(EntityKey key, int bitmask) {
    if (key.index < 0 || key.index >= MAX_ENTITIES) {
        return;
    }
    entity_bitmasks[key.index] = bitmask;
}

int entity_bitmasks_init() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entity_bitmasks[i] = 0;
    }
    return 1;
}
