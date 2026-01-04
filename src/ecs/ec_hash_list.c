#include <stdio.h>
#include <string.h>
#include "ecs/ec_hash_list.h"


int hash_int(int i){
    return i % LIST_SIZE;
}

void initialize_ec(EntityComponent *ec, int id, int c_indx){
    ec->ent_id = id;
    ec->component_index = c_indx;
    return;
}

void copy_ec_to_bucket(ECBucket list[], EntityComponent *ec){
    int hash = hash_int(ec->ent_id);
    while(list[hash].current_size>=BUCKET_SIZE){
	hash = hash_int(hash+1);
    }
    ECBucket *b = &list[hash];
    b->bucket[b->current_size] = *ec; 
    b->current_size += 1;
    return;
}

EntityComponent* search_ec_in_bucket(ECBucket list[], int ec_id, int bucket_index){
    ECBucket *b = &list[bucket_index];
    int i = 0;
    while(i < b->current_size){
	if(b->bucket[i].ent_id == ec_id){
	    return &b->bucket[i];
	}
    }
    //printf("Entity not found in current bucket, should search in next one \n");
    return NULL;
}

//===============================
//publics
int ec_exists(ECBucket list[], int id){
    int hash = hash_int(id);
    if(search_ec_in_bucket(list, id, hash) == NULL){
	printf("ec doesnt exist in hash bucket \n ");
	return 0;
    }
    return 1;
}

int ec_exists_no_warning(ECBucket list[], int id){
    int hash = hash_int(id);
    if(search_ec_in_bucket(list, id, hash) == NULL){
	return 0;
    }
    return 1;
}

void print_comp(ECBucket list[], int id){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(list, id, hash);
    printf("ent_id %u \n", ec->ent_id);
    printf("component index %u \n", ec->component_index);
}

void test_ec(ECBucket list[], int id){
    ec_exists(list, id);
    print_comp(list, id);
}

int init_ec_hash_list(ECBucket list[]){
    int i;
    for(i = 0; i < LIST_SIZE ; i++){
	list[i].current_size = 0;
    }
    if (i == LIST_SIZE){
	return 1;
    }
    return 0;
}

void register_ec(ECBucket list[], int id, int component_index){
    if (ec_exists_no_warning(list, id) == 1){
	change_ec(list, id, component_index);
	printf("mete un cambio al registrar, osea q ya habia algo registrado \n");
    }
    EntityComponent ec;
    initialize_ec(&ec, id, component_index);
    copy_ec_to_bucket(list, &ec);
    //test_ec(id);
}

void change_ec(ECBucket list[], int id, int n_component_index){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(list, id, hash);
    if(ec == NULL){
	printf("Couldnt find the EC to change the value \n");
	return;
    }
    ec->component_index = n_component_index;
}


int is_ec_registered(ECBucket list[], int id){
    return ec_exists(list, id);
}

int get_component_index_by_id(ECBucket list[], int id){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(list, id, hash);
    if(ec != NULL){
	return ec->component_index;
    }
    return -1;
}

int get_component_index_by_id_no_warning(ECBucket list[], int id){
    int hash = hash_int(id);
    EntityComponent *ec = search_ec_in_bucket(list, id, hash);
    if(ec != NULL){
	return ec->component_index;
    }
    return -1;
}

