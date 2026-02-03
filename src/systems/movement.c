// src/systems/movement.c
#include <stdio.h>
#include <stdlib.h>

#include "game_state.h"
#include "systems/movement.h"
#include "components/direction_vec_comp.h"
#include "components/position_comp.h"
#include "components/entity_bitmasks.h"
#include "entities.h"

int movement_system_tick(void *v_ents, float delta){
    Position *positions = positions_get();
    DirectionVec *direction_vecs = direction_vecs_get();
    int pos_count = position_count_get();
    int *ent_bitmasks = entity_bitmasks;
    
    int speed = 200;
    
    // ⭐ ITERACION EFICIENTE: Solo sobre entidades con posición
    for (int pos_idx = 0; pos_idx < pos_count; pos_idx++) {
        
        // Obtener índice de entidad desde la posición
        int entity_idx = position_to_entity_index_get(pos_idx);
        if (entity_idx < 0) {
            continue;
        }
        
        // ⭐ Acceso O(1) al bitmask desde array global
        int components_mask = ent_bitmasks[entity_idx];
        
        // Verificar si es movible
        if ((components_mask & IS_MOVABLE_MASK) == 0) {
            continue;
        }
        
        // Obtener dirección vector
        EntityKey ent_key = position_get_entity_by_index(pos_idx);
        int dvi = direction_vec_index_get_from_key(ent_key);
        if (dvi < 0) {
            continue;  // No tiene componente de direction vec
        }
        
        // ⭐ Acceso directo
        Position *pos = &positions[pos_idx];
        DirectionVec dvec = direction_vecs[dvi];
        
        if (components_mask & IS_PLAYER_MASK) {
            int mov = (int)(speed * delta);
            pos->x += mov * dvec.x;
            pos->y += mov * dvec.y;
        }
    }
    
    return 1;
}
