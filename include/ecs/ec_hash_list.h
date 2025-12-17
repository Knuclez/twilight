#ifndef EC_LIST_TEMPLATE_H
#define EC_LIST_TEMPLATE_H 

#define LIST_SIZE 50
#define BUCKET_SIZE 10
#define MAX_ENTITIES (LIST_SIZE*BUCKET_SIZE)

typedef struct {
    int ent_id;
    int component_index;
} EntityComponent;

typedef struct {
    int current_size;
    EntityComponent bucket[BUCKET_SIZE];
} ECBucket;

int init_ec_hash_list(ECBucket list[]);
void register_ec(ECBucket list[], int id, int component_index); 
int is_ec_registered(ECBucket list[], int id);
int get_component_index_by_id(ECBucket list[], int id);
#endif
