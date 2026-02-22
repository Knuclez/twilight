#ifndef ACTIONQ_H
#define ACTIONQ_H

#include "entities.h"

#define MAX_ACTIONS 64

typedef enum {
    PLAYER_ATTACK,
} ActionType;


typedef union {
    EntityKey attacker_key;
} ActionData;

typedef struct {
    ActionType type;
    ActionData data;
} Action;

typedef struct {
    Action queue[MAX_ACTIONS];
    int actions_amount;
} ActionQueue;


int get_actions_amount(void);
Action* get_actions_queue(void);
void queue_action(Action a);
void clean_action_queue();
#endif
