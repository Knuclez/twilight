#include <stdio.h>
#include "entities.h"

EntityKey entities[200];


EntityKey* entities_get(){
    return entities;
}

int entities_amount(){
    return 200;
}

EntityKey entity_create(){
    EntityKey new;
    new.index = -1;
    new.generation = -1;
    for(int i = 0; i < 200; i++){
	if(entities[i].index == -1){
	    new.index = i;
	    new.generation = entities[i].generation + 1;
	    entities[i] = new;	    
	    return entities[i];
	}
    }
    return new;
}

void entity_add_bitmask(EntityKey key, int n_bitmas){
    if(entities[key.index].generation == key.generation){
	entities[key.index].bitmask = n_bitmas;
	return;
    }
    printf("generation dont match for index %u\n", key.index);
    return;
}


void entities_list_init(){
    for(int i = 0; i<200;i++){
	EntityKey new;
	new.index = -1;
	new.generation = 0;
	new.bitmask = 0;
	entities[i] = new;
    }
}
