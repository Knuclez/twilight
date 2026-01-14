#include <stdio.h>
#include <string.h>
#include "storage_structures/ec_hash_list.h"


int hash_int(int i){
    return i % LIST_SIZE;
}

void initialize_ec(EntityComponent *ec, EntityKey key, int c_indx){
    ec->ent_key = key;
    ec->component_index = c_indx;
    return;
}

void copy_ec_to_bucket(ECBucket list[], EntityComponent *ec){
    int hash = hash_int(ec->ent_key.index);
    while(list[hash].current_size>=BUCKET_SIZE){
	hash = hash_int(hash+1);
    }
    ECBucket *b = &list[hash];
    b->bucket[b->current_size] = *ec; 
    b->current_size += 1;
    return;
}

EntityComponent* search_ec_in_bucket(ECBucket list[], EntityKey ec_key, int bucket_index){
    ECBucket *b = &list[bucket_index];
    int i = 0;
    while(i < b->current_size){
	EntityKey i_ec_key = b->bucket[i].ent_key;
	if(i_ec_key.generation == ec_key.generation && i_ec_key.index == ec_key.index){
	    return &b->bucket[i];
	}
    }
    //printf("Entity not found in current bucket, should search in next one \n");
    return NULL;
}

//===============================
//publics
int ec_exists(ECBucket list[], EntityKey key){
    int hash = hash_int(key.index);
    if(search_ec_in_bucket(list, key, hash) == NULL){
	printf("ec doesnt exist in hash bucket \n ");
	return 0;
    }
    return 1;
}

int ec_exists_no_warning(ECBucket list[], EntityKey key){
    int hash = hash_int(key.index);
    if(search_ec_in_bucket(list, key, hash) == NULL){
	return 0;
    }
    return 1;
}

void ec_comp_print(ECBucket list[], EntityKey key){
    int hash = hash_int(key.index);
    EntityComponent *ec = search_ec_in_bucket(list, key, hash);
    printf("ent_key_index %u \n", ec->ent_key.index);
    printf("component index %u \n", ec->component_index);
}

void ec_test(ECBucket list[], EntityKey key){
    ec_exists(list, key);
    ec_comp_print(list, key);
}

int ec_hash_list_init(ECBucket list[]){
    int i;
    for(i = 0; i < LIST_SIZE ; i++){
	list[i].current_size = 0;
    }
    if (i == LIST_SIZE){
	return 1;
    }
    return 0;
}

void ec_value_change(ECBucket list[], EntityKey key, int n_component_index){
    int hash = hash_int(key.index);
    EntityComponent *ec = search_ec_in_bucket(list, key, hash);
    if(ec == NULL){
	printf("Couldnt find the EC to change the value \n");
	return;
    }
    ec->component_index = n_component_index;
}

void ec_register(ECBucket list[], EntityKey key, int component_index){
    if (ec_exists_no_warning(list, key) == 1){
	ec_value_change(list, key, component_index);
	printf("mete un cambio al registrar, osea q ya habia algo registrado \n");
    }
    EntityComponent ec;
    initialize_ec(&ec, key, component_index);
    copy_ec_to_bucket(list, &ec);
    //test_ec(id);
}

int is_key_registered(ECBucket list[], EntityKey key){
    return ec_exists(list, key);
}

int component_index_get(ECBucket list[], EntityKey key){
    int hash = hash_int(key.index);
    EntityComponent *ec = search_ec_in_bucket(list, key, hash);
    if(ec != NULL){
	return ec->component_index;
    }
    printf("nao existe id: %u en component\n", key.index);
    return -1;
}

int component_index_get_no_warning(ECBucket list[], EntityKey key){
    int hash = hash_int(key.index);
    EntityComponent *ec = search_ec_in_bucket(list, key, hash);
    if(ec != NULL){
	return ec->component_index;
    }
    return -1;
}

