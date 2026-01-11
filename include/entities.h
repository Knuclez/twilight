#ifndef ENTITIES_H
#define ENITIES_H

typedef struct {
    int id;
    int generation;
} EntityKey;

void init_entities_list();
EntityKey* new_entity();
#endif
