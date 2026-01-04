#ifndef SIZE_ECS_H 
#define SIZE_ECS_H 

typedef struct {
    int h;
    int w;
} Size;

int init_size_ecs();
void add_size_component_to_id(int id, int w, int h);
int get_size_component_amount();
void remove_size_from_id(int id);
Size* get_id_associated_size(int id);
Size* get_size_by_index(int indx);

#endif
