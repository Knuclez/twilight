// src/systems/movement.c
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "systems/movement.h"
#include "entities.h"  /* unified storage, includes bitmask macros */

/* old SoA component includes have been removed; component data now lives
   directly inside the Entity struct. */

static int would_collide(Entity *ents, int max, Entity *mover, int test_x, int test_y){
    int a_l = test_x - mover->size.x + mover->physical_bounds.x;
    int a_r = test_x - mover->size.x + mover->physical_bounds.x + mover->physical_bounds.width * 2;
    int a_t = test_y - mover->size.y + mover->physical_bounds.y;
    int a_b = test_y - mover->size.y + mover->physical_bounds.y + mover->physical_bounds.height * 2;

    for (int i = 0; i < max; i++){
        Entity *o = &ents[i];
        if (o->key.index <= 0)                   continue;
        if (o->key.index == mover->key.index)    continue;
        if (!(o->bitmask & HAS_COLIDER_MASK))    continue;
        if (o->bitmask & IS_DAMAGE_MASK)         continue;
        if (o->bitmask & IS_PLAYER_MASK)         continue;
        if (entity_get_combat_type(o->key) == MOB) continue;

        int b_l = o->position.x - o->size.x + o->physical_bounds.x;
        int b_r = o->position.x - o->size.x + o->physical_bounds.x + o->physical_bounds.width * 2;
        int b_t = o->position.y - o->size.y + o->physical_bounds.y;
        int b_b = o->position.y - o->size.y + o->physical_bounds.y + o->physical_bounds.height * 2;

        if (a_r > b_l && a_l < b_r && a_b > b_t && a_t < b_b)
            return 1;
    }
    return 0;
}

int movements_process_frame(void *v_ents, float delta){
    Entity *ents = (Entity*) v_ents;
    int max   = entities_max_index();
    int speed = 200;

    for (int i = 0; i < max; i++){
        Entity *e = &ents[i];
        if (e->key.index < 0)                       continue;
        if ((e->bitmask & IS_MOVING_MASK) == 0)     continue;

        int dx = (int)(speed * delta) * e->direction_vec.x / 10;
        int dy = (int)(speed * delta) * e->direction_vec.y / 10;

        /* axis-separated sweep: allows sliding along walls on diagonals */
        if (dx != 0 && !would_collide(ents, max, e, e->position.x + dx, e->position.y))
            e->position.x += dx;

        if (dy != 0 && !would_collide(ents, max, e, e->position.x, e->position.y + dy))
            e->position.y += dy;
    }

    return 1;
}
