#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "action_q.h"
//action_q declared in action_q.h

ActionQueue action_q = {0};

int get_actions_amount(){
    return action_q.actions_amount;
}

Action* get_actions_queue(){
    return action_q.queue;
}

void queue_action(Action action){
    if (action_q.actions_amount < MAX_ACTIONS){
	action_q.queue[action_q.actions_amount] = action;
	action_q.actions_amount ++;
    } else {
	printf("surpassed amount of max actions per frame \n");
    }
};

void clean_action_queue(){
    for (int i = 0; i < action_q.actions_amount; i++){
	int *to_free = action_q.queue[i].data;
	free(to_free);
	memset(&(action_q.queue[i]), 0 , sizeof(Action));
    }
    action_q.actions_amount = 0;
};
