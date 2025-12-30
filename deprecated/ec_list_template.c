#include <stdio.h>
#include <string.h>
#include "ecs/ec_list_template.h"

#define LIST_SIZE 200
#define BUCKET_SIZE 10


typedef struct {
    int value;
} Component;

typedef struct {
    int ent_id;
    Component component;
} EntityComponent;

typedef struct {
    int current_size;
    EntityComponent bucket[BUCKET_SIZE];
} ECBucket;

ECBucket bucket_list[LIST_SIZE];

int hash_int(int i){
    return i % LIST_SIZE;
}

void initialize_component(Component *c,int n_value){
    c->value = n_value;
    return;
}

void initialize_ec(EntityComponent *ec, int id){
    ec->ent_id = id;
    return;
}

void add_component_to_ec(EntityComponent* ec, Component *i_comp){
    ec->component = *i_comp;
}

void copy_ec_to_bucket(EntityComponent *ec){
    int hash = hash_int(ec->ent_id);
    while(bucket_list[hash].current_size>=BUCKET_SIZE){
	hash = hash_int(hash+1);
    }
    ECBucket *b = &bucket_list[hash];
    b->bucket[b->current_size] = *ec; 
    b->current_size += 1;
    return;
}

EntityComponent* search_ec_in_bucket(int ec_id, int bucket_index){
    ECBucket *b = &bucket_list[bucket_index];
    int i = 0;
    while(i < b->current_size){
	if(b->bucket[i].ent_id == ec_id){
	    return &b->bucket[i];
	}
    }
    printf("Entity not found in current bucket, should search in next one \n");
    return NULL;
}

//===============================
//publics
void ec_exists(int id){
    int hash = hash_int(id);
    if(search_ec_in_bucket(id, hash) == NULL){
	printf("ec doesnt exist in hash bucket \n ");
    }
}

void print_comp(int id){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(id, hash);
    printf("ent_id %u \n", ec->ent_id);
    printf("component value %u \n", ec->component.value);
}

void test_ec(int id){
    ec_exists(id);
    print_comp(id);
}

void init_ec_hash_list(){
    int i;
    for(i = 0; i < LIST_SIZE ; i++){
	bucket_list[i].current_size = 0;
    }
}

void register_entity(int id, int val){
    EntityComponent ec;
    Component c;
    initialize_component(&c, val);
    initialize_ec(&ec, id);
    add_component_to_ec(&ec, &c); 
    copy_ec_to_bucket(&ec);
    //test_ec(id);
}

Component* get_component_by_id(int id){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(id, hash);
    if(ec != NULL){
	return &ec->component;
    }
}


