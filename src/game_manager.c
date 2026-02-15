#include <stdio.h>
#include "tools/console.h"
#include "game_manager.h"
#include "game_state.h"
#include "action_q.h"
#include "interface/animations_rsc.h"

//#include "entities.h"
#include "systems/movement.h"
#include "systems/combat.h"
#include "entities.h"  /* lifetime handled inside Entity */

int last_second = 0;

void initialize_game_systems(){
    entities_list_init();
    console_init();

    if(initialize_game_state() == 0){
	printf("failiure initializing game state \n");
    }

}

void process_action_q(int current_time){
    int actn_amt = get_actions_amount();
    Action *act_list = get_actions_queue();
    for(int i = 0; i < actn_amt ; i++){
	Action actn = *(act_list + i);
	switch(actn.type){
	    case PLAYER_ATTACK:
		int attacker_indx = *(actn.data);
		int attacker_generation = *(actn.data + 1);
		combat_process_attack(attacker_indx, attacker_generation);
		break;
	}
    }
    clean_action_queue();
}

void tick_lifetimes() {
    for (int i = 0; i < entities_max_index(); i++) {
        Entity *e = &entities[i];
        if (e->key.index < 0) continue;
        if (e->lifetime > 0) {
            e->lifetime--;
	    printf("lifetime %u\n", e->lifetime); 
            if (e->lifetime <= 0) {
                /* mark as dead by bumping generation and clearing bitmask */
                e->key.generation++;
                e->bitmask = 0;
                e->key.index = -1;
            }
        }
    }
}

void tick_animations(float delta_time, float frame_rate) {
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

void collisions_process_frame(void *v_ents){
    Entity *ents = (Entity*) v_ents;
    for (int i = 0; i < entities_max_index(); i++) {
        Entity *e = &entities[i];
        if (e->key.index <= 0) continue;
        if (e->bitmask & HAS_COLIDER_MASK) {
		printf("%u has colider\n", e->key.index);
	}
    } 
    return;
}

void update(int current_time, float delta){
    Entity *ents = entities_get();
    process_action_q(current_time);
    movements_process_frame((void*)ents, delta);
    collisions_process_frame((void*)ents);
    tick_animations(delta, 30.0f);
    if (current_time > last_second + 1000){
        tick_lifetimes();
        last_second = current_time;
    }
    return;
}


