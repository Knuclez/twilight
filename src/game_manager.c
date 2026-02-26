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

void tick_animations(float delta_time) {
    Entity *entities = entities_get();
    AnimationClip *clips = animation_clips_get();
    AnimationSet  *sets  = animation_sets_get();
    for (int i = 0; i < entities_max_index(); i++) {
        Entity *e = &entities[i];
        if (e->key.index < 0) continue;
        if (!(e->bitmask & HAS_ANIMATION_MASK)) continue;
        int clip_idx = animation_get_clip_for_entity(e->animation.anim_set_index,
                                                     e->combat_state, e->direction);
        AnimationClip clip = clips[clip_idx];
        if (clip.fps <= 0.0f || clip.frame_count <= 1) continue;
        e->animation.frame_timer += delta_time;
        float frame_length = 1.0f / clip.fps;
        if (e->animation.frame_timer >= frame_length) {
            e->animation.frame_timer -= frame_length;
            e->animation.current_frame++;
            if (e->animation.current_frame >= clip.frame_count) {
                e->animation.current_frame = clip.loop ? 0 : clip.frame_count - 1;
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
    tick_animations(delta);
    clean_queues(gs);
    if (current_time > last_second + 1000){
        tick_lifetimes();
        last_second = current_time;
    }
    return;
}


