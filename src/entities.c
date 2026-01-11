#include <stdio.h>
#include "entities.h"

EntityKey entities[200];
int last_id;

EntityKey* new_entity(){
    for(int i = 0; i < 200; i++){
	if(entities[i].id == -1){
	    EntityKey new;
	    new.id = last_id + 1;
	    new.generation = entities[i].generation + 1;
	    last_id ++;
	    entities[i] = new;	    
	    return &entities[i];
	}
    }
    return NULL;
}


void init_entities_list(){
    for(int i = 0; i<200;i++){
	EntityKey new;
	new.id = -1;
	new.generation = 0;
	entities[i] = new;
    }
}
