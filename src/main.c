#include <stdio.h>
#include <SDL2/SDL.h>
#include "interface/rendering/render_main.h"
#include "interface/input.h"
#include "game_manager.h"

const int FPS = 30;
const int FRAME_TIME = 1000/ FPS;
int looping;
Uint32 last_frame_time;

int initialize_stuff(){
    looping = initialice_sdl();
    if (looping == 0){
	printf("Error initializing SDL\n");
	return 0;
    }

    initialize_game_systems();
    last_frame_time = SDL_GetTicks();

    return 1;
}

void terminate_stuff(){
    terminate_sdl();
}

int main(int argc, char* argv[])
{
    if ((initialize_stuff()) == 0){
	return 0;
    }

    Uint32 last_frame_time = SDL_GetTicks();
    while(looping){
	Uint32 current_time = SDL_GetTicks();
	Uint32 elapsed_time = current_time - last_frame_time;
	last_frame_time = current_time;

	float delta = elapsed_time / 1000.0f;

	process_input(&looping);
	update(delta);
	render();

	Uint32 frame_time = SDL_GetTicks() - current_time;
	if (frame_time < FRAME_TIME) {
	    SDL_Delay(FRAME_TIME - frame_time);
	}
    }
  
    terminate_stuff();
    return 0;
}
