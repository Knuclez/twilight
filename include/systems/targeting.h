#ifndef TARGETING_SYS_H
#define TARGETING_SYS_H

#include "ecs/position_ecs.h"

void scan_for_food(int cow_id, Position *cow_pos);
void remove_target_entity(int tgt_id);
#endif
