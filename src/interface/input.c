#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/gui_entities.h"
#include "interface/input.h"
#include "interface/screens_switch.h"


int check_for_clicked_entity(int x, int y){
    ComponentList *click_list = get_click_entities();
    if (click_list == NULL){
	return -1;
    }
    //si el click esta entre los boundes, dame el de mayor orden Z
    GUI_Entity res = {.id = -1};
    int len = sizeof(GUI_Entity) * click_list->amount; 
    GUI_Entity *res_l = malloc(len);
    int res_quant = 0;

    for (int i = 0; i < click_list->amount; i++){
	GUI_Entity *ent = (click_list->list)[i];
	SDL_Rect ent_rect = ent->rect; //la lista de entities ocn el componente de activas
	if ( x< ent_rect.x ||
		ent_rect.x + ent_rect.w < x){
	    continue;
	}
	if ( y<ent_rect.y ||
		ent_rect.y + ent_rect.h < y){
	    continue;
	}
	res_l[res_quant] = *ent;
	res_quant++;
    }
    if (res_quant > 0){
	res = res_l[0];
	for(int j = 1; j < res_quant; j++){
	    if(res_l[j].z > res.z){
		res = res_l[j];
	    }
	}
    }
    return res.id; 
}

void interpret_mouse_button(SDL_Event event){
    int id_res = check_for_clicked_entity(event.button.x, event.button.y);
    if (id_res == -1){
	return;
    }
    scene_switch_mouse_button(id_res);
    return;
}

void interpret_input_event(SDL_Event event){
    scene_switch_input_event(event);
}

void interpret_keydown(SDL_Event event, int *looping){
    if (event.key.keysym.sym == SDLK_ESCAPE){
	*looping = 0;
    }
    scene_switch_keydown(event);
}

void process_input(int *looping){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
	switch(event.type){
	    case SDL_QUIT:
		*looping = 0;
		break;
	    case SDL_KEYDOWN:
		interpret_keydown(event, looping);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		interpret_mouse_button(event);
	        break;
	    case SDL_TEXTINPUT:
		interpret_input_event(event);

	}
    }
}

