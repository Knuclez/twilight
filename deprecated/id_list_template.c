#ifndef ID_LIST_TEMPLATE_H
#define ID_LIST_TEMPLATE_H

typedef struct {
    int amount;
    int size;
    int *data;
} IdList;

void initialize_idlist(IdList *l);
void register_id_to_idlist(IdList *l, int id);
int get_id_by_index(IdList *l, int index);

#endif
