#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/input.h"
#include "interface/screens_switch.h"



int check_for_clicked_entity(int x, int y){
    /*
    int clickAmount = get_clickable_comp_amount();
    int* clickList = get_clickable_entities();
    int id = -1; 
    for (int i = 0; i < clickAmount; i++){
	id = *(clickList + i);
	Position *pos = get_id_associated_position(id);
	Size *size = get_id_associated_size(id);
	if ( x< pos->x ||
		pos->x + size->w < x){
	    continue;
	}
	if ( y<pos->y ||
		pos->y + size->h < y){
	    continue;
	}
    }

    /*
    if (res_quant > 0){
	res = res_l[0];
	for(int j = 1; j < res_quant; j++){
	    if(res_l[j].z > res.z){
		res = res_l[j];
	    }
	}
    }
    return id; 
    */
    return 0; 
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

