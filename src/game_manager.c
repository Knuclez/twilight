#include <stdio.h>
#include "tools/console.h"
#include "game_manager.h"
#include "game_state.h"
#include "action_q.h"

//#include "entities.h"
#include "systems/movement.h"



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
	    case ANIMAL_EAT:
		int cow_id = *(actn.data);
		int tgt_id = *(actn.data + 1);
		//start_digestion(cow_id);
		//remove_target_entity(tgt_id);
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


