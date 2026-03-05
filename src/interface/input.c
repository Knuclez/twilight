#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/screen.h"
#include "interface/input.h"
#include "input_handler.h"
#include "editor/editor_main.h"


SDL_GameController *controller = NULL;

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

    if (res_quant > -1){
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
    if(editor_is_active()){
	editor_mouse_button_clicked(event);
	return;
    }
    int id_res = check_for_clicked_entity(event.button.x, event.button.y);
    if (id_res == -1){
	return;
    }
    screen_entity_clicked(id_res);
    return;
}

void interpret_text_event(SDL_Event event){
    screen_text_event(event);
}

void interpret_keydown(SDL_Event event, int *looping){
    if (event.key.keysym.sym == SDLK_ESCAPE){
	*looping = 0;
    }
    if (event.key.keysym.sym == SDLK_F3){
	editor_toggle();
	return;
    }
    if(editor_is_active()){
	editor_interpret_key_event(event);
    }
    event_key_down_handle(event);
}

void interpret_keyup(SDL_Event event){
    event_key_up_handle(event);
}

void controller_read_axis(SDL_GameController *contr){
    Sint16 axisX = SDL_GameControllerGetAxis(contr, SDL_CONTROLLER_AXIS_LEFTX);
    Sint16 axisY = SDL_GameControllerGetAxis(contr, SDL_CONTROLLER_AXIS_LEFTY);

    controller_axis_interpret((int)axisX, (int)axisY);
    return;
}


void try_controller_connection(){
	if(SDL_NumJoysticks() > 0){
	    if(SDL_IsGameController(0)){
		controller = SDL_GameControllerOpen(0);
		printf("joystick 0 connected \n");
	    } 
	    else {
		printf("joystick 0 is not a game_controller\n");
	    }
	}
	else {
	    printf("No connected joysticks\n");
	}
}

void input_init(){
    SDL_JoystickEventState(SDL_ENABLE);
    try_controller_connection();
}

void process_input(int *looping){
    SDL_Event event;
    if(controller != NULL){
	controller_read_axis(controller);
    }

    while(SDL_PollEvent(&event)){
	switch(event.type){
	    case SDL_QUIT:
		*looping = 0;
		break;
	    case SDL_KEYDOWN:
		interpret_keydown(event, looping);
		break;
	    case SDL_KEYUP:
		interpret_keyup(event);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		interpret_mouse_button(event);
	        break;
	    case SDL_TEXTINPUT:
		interpret_text_event(event);
		break;
	    case SDL_JOYDEVICEADDED:
		printf("num de joysticks %u\n", SDL_NumJoysticks());
		if(controller == NULL){
		    try_controller_connection();
		}
		break;
	    case SDL_JOYDEVICEREMOVED:
		if(controller != NULL &&
		   SDL_GameControllerGetJoystick(controller) == SDL_JoystickFromInstanceID(event.jdevice.which)){
		    SDL_GameControllerClose(controller);
		    controller = NULL;
		    printf("controller disconnected\n");
		}
		break;
	}
    }
}

