#include <stdio.h>
#include "tools/console.h"
#include "game_manager.h"
#include "game_state.h"
#include "action_q.h"

//#include "entities.h"
#include "systems/movement.h"
#include "systems/combat.h"


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

void update(int current_time, float delta){
    EntityKey *ents = entities_get();
    process_action_q(current_time);
    movement_system_tick((void*)ents, delta);
    return;
}


