#ifndef EC_HASH_LIST
#define EC_HASH_LIST

#include "entities.h"


typedef struct {
    EntityKey ent_key;
    int component_index;
} EntityComponent;

typedef struct {
    int current_size;
    EntityComponent bucket[BUCKET_SIZE];
} ECBucket;

int ec_exists(ECBucket list[], EntityKey key);
int ec_exists_no_warning(ECBucket list[], EntityKey key);
void ec_comp_print(ECBucket list[], EntityKey key);
void ec_test(ECBucket list[], EntityKey key);
int is_key_registered(ECBucket list[], EntityKey key);

int ec_hash_list_init(ECBucket list[]);
void ec_register(ECBucket list[], EntityKey key, int component_index);
void ec_value_change(ECBucket list[], EntityKey key, int n_component_index);
int component_index_get(ECBucket list[], EntityKey key);
int component_index_get_no_warning(ECBucket list[], EntityKey key);
#endif
