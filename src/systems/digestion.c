#include <stdio.h>
#include <stdlib.h>
#include "systems/digestion.h"
#include "scenes/field_scene.h"
#include "ecs/position_ecs.h"

typedef int TimeStamp;

DigestionNode *time_buckets[MAX_TIME];

TimeStamp last_second = 0;

void start_digestion(int n_animal_id){
    DigestionNode *last_node = time_buckets[MAX_TIME - 1];
    DigestionNode new;
    new.animal_id = n_animal_id; 
    new.previous_node = last_node;
    //printf("previous node: %p \n", new.previous_node);
    DigestionNode *p = malloc(sizeof(DigestionNode));
    *p = new;
    time_buckets[MAX_TIME-1] = p;
    //printf("new last: %p \n", last_node);
    return;
}

void free_digestions(){
    DigestionNode *to_clean = time_buckets[0];
    DigestionNode *next;    
    //printf("%p to clean \n", to_clean);
    while(to_clean != NULL){
	Position *cow_pos = get_id_associated_position(to_clean->animal_id);
	instance_poo(108, cow_pos->x, cow_pos->y);
	next = to_clean->previous_node;
	free(to_clean);
	to_clean = next;
	//printf("to_clean : %p \n", to_clean);
    }
    //printf("termina digestions \n");
}

void move_buckets_pointers() {
    for(int i = 0; i < MAX_TIME-1; i++){
	if(i == 0){
	    free_digestions();
	}
	//printf("actual pos %u = %p \n",i,  time_buckets[i]);
	time_buckets[i] = time_buckets[i+1];
	//printf("new pos %u = %p \n",i , time_buckets[i]);
    }
    //printf("%p ultimo bucket antes \n", time_buckets[MAX_TIME-1]);
    time_buckets[MAX_TIME - 1] = NULL;
    //printf("%p ultimo bucket despues \n", time_buckets[MAX_TIME-1]);
}

void tick_digestion_system(TimeStamp current_time){
    int one_second = 1000;
    if(current_time > last_second + one_second){
	//printf("second: %u \n", last_second);
	move_buckets_pointers();
	//printf("termina el second \n");
	last_second = current_time;
    }

}

void init_digestion_system(){
   for(int i = 0; i < MAX_TIME; i++){
    time_buckets[i] = NULL; 
   } 
   return;
}
