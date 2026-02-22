#include <stdio.h>
#include "tools/console.h"
#include "game_manager.h"
#include "game_state.h"
#include "action_q.h"
#include "interface/animations_rsc.h"

#include "systems/movement.h"
#include "systems/combat.h"
#include "entities.h"  /* lifetime handled inside Entity */

int last_second = 0;

void initialize_game_systems(){
    console_init();

    if(initialize_game_state() == 0){
	printf("failiure initializing game state \n");
    }

}

void process_action_q(int current_time){
    int actn_amt = get_actions_amount();
    Action *act_list = get_actions_queue();
    for(int i = 0; i < actn_amt ; i++){
	Action actn = act_list[i];
	switch(actn.type){
	    case PLAYER_ATTACK:
		// Accedemos directamente a la struct en la union
		combat_process_attack(actn.data.attacker_key);
		break;
	    	}
    }
    clean_action_queue();
}

void tick_lifetimes() {
    Entity *entities = entities_get();
    for (int i = 0; i < entities_max_index(); i++) {
        Entity *e = &entities[i];
        if (e->key.index < 0) continue;
        if (e->lifetime > 0) {
            e->lifetime--;
            if (e->lifetime <= 0) {
                /* mark as dead by bumping generation and clearing bitmask */
               entity_deactivate(entities, e->key); 
            }
        }
    }
}

void tick_animations(float delta_time, float frame_rate) {
    Entity *entities = entities_get();
    for (int i = 0; i < entities_max_index(); i++) {
        Entity *e = &entities[i];
        if (e->key.index < 0) continue;
        if ((e->bitmask & HAS_ANIMATION_MASK) &&
            e->animation.resource_index >= 0) {
            e->animation.frame_timer += delta_time;
            float frame_length = 1.0f / frame_rate;
            if (e->animation.frame_timer >= frame_length) {
                e->animation.frame_timer -= frame_length;
                e->animation.current_frame++;
                
                /* wrap-around: need to get the frame count from animation resource */
                AnimationRsc* anim_rscs = animation_rscs_get();
                if (e->animation.resource_index < 10) { /* assuming max 10 resources */
                    int frame_count = anim_rscs[e->animation.resource_index].frame_amount;
                    if (frame_count > 0 && e->animation.current_frame >= frame_count) {
                        e->animation.current_frame = 0;
                    }
                }
            }
        }
    }
}


void clean_queues(GameState *gs){
    collision_queue_clear(&gs->collision_queue);
}

void update(int current_time, float delta){
    GameState *gs = get_game_state_p();
    Entity *ents = entities_get();
    process_action_q(current_time);
    movements_process_frame((void*)ents, delta);
    combat_system_tick(gs);
    tick_animations(delta, 30.0f);
    clean_queues(gs);
    if (current_time > last_second + 1000){
        tick_lifetimes();
        last_second = current_time;
    }
    return;
}


