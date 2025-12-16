#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "interface/rendering/gui_entities.h"
#include "interface/scenes.h"

GUI_Entity *all_entities;
ComponentList click_entities;
ComponentList text_edit_entities;

int entities_amount;
int current_size;

GUI_Entity* get_entity_by_id(int l_id){
    for(int i = 0; i < entities_amount; i++){
	if (all_entities[i].id == l_id){
	    return &(all_entities[i]);
	}
    }
    printf("ID %u not found in entity list \n", l_id);
    return NULL;
}

ComponentList* get_click_entities(){
    return &click_entities;
}

void alloc_comp_list(ComponentList *l){
    l->list = malloc(sizeof(GUI_Entity*) * 2);
    memset(l->list, 0, sizeof(GUI_Entity*) * 2);
    if (l->list == NULL){
	printf("Error creating space for click_entieties");
    }
    l->amount = 0;
    l->size = 2;
}

void alloc_gui_entities_space(){
    all_entities = malloc(sizeof(GUI_Entity) * 2);
    memset(all_entities, 0, sizeof(GUI_Entity) * 2);
    if (all_entities == NULL){
	printf("Error creating space for GUI_entities");
    }
    entities_amount = 0;
    current_size = 2;
    
    alloc_comp_list(&click_entities);
    alloc_comp_list(&text_edit_entities);
}

void free_entities_space(){
    free(click_entities.list);
    free(text_edit_entities.list);
    free(all_entities);
}

void unload_scene_gui_entities(){
    free_entities_space();
    alloc_gui_entities_space();
}

void expand_component_space(ComponentList *c_list){
    int new_size = c_list->size * 2;
    GUI_Entity **np = realloc(c_list->list, sizeof(GUI_Entity*) * new_size);
    if (np == NULL){
	printf("Error allocating more space for c_list");
    }
    c_list->list = np;
    c_list->size = new_size;
}

void expand_entities_space(){
    int new_size = current_size * 2;
    GUI_Entity *np = realloc(all_entities, sizeof(GUI_Entity) * new_size);
    if (np == NULL){
	printf("Error allocating more space for GUI_entities");
    }
    all_entities = np;
    current_size = new_size;
}

void add_to_component_list(ComponentList *c_list, GUI_Entity *ent){
    if(c_list->size == c_list->amount){
	expand_component_space(c_list);
    }
    c_list->list[c_list->amount] = ent;
    printf("id es %u \n", (c_list->list[c_list->amount])->id);
    c_list->amount += 1;
}

GUI_Entity instance_new_entity(SDL_Rect r_rect,SDL_Texture *r_txt,int r_id, int r_z, unsigned char r_flags){
    GUI_Entity new = {.id = r_id, 
		    .rect = r_rect,
		    .txt = r_txt,
		    .z = r_z,
		    .flags = r_flags};
    return new;
}


//LAS FLAGS ESTAS PODRIAN CAMBIAR EN CADA IMPLEMENTACION
void append_to_component_lists(GUI_Entity *ent){
    if(ent->flags & 0x01){
	add_to_component_list(&click_entities, ent);
    }
    if (ent->flags & 0x02){
	printf("size %u \n", text_edit_entities.amount);
	add_to_component_list(&text_edit_entities, ent);
	printf("size %u \n", text_edit_entities.amount);
    }
}

void append_new_entity(SDL_Rect rect,SDL_Texture *txt, int id, int z, unsigned char flags){
    GUI_Entity new_entity = instance_new_entity(rect, txt, id, z, flags);
    if (entities_amount == current_size){
	expand_entities_space();
    }
    all_entities[entities_amount] = new_entity;		
    append_to_component_lists(&all_entities[entities_amount]);
    entities_amount++;
}


