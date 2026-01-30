#include <SDL2/SDL.h>
#include <stdio.h>

#include "interface/rendering/render_main.h"
#include "interface/rendering/render_auxs.h"
#include "interface/rendering/texturing.h"
#include "interface/screen.h"
#include "interface/animations_rsc.h"

SDL_Window* window;
SDL_Renderer* renderer;


void* get_renderer(){
    return (void*)renderer;
}

int initialice_sdl(){
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) < 0){
	printf("Error initiatin SDL %s \n", SDL_GetError());
	return 0;
    }
     window = SDL_CreateWindow("Hola",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				800, 600,
				SDL_WINDOW_OPENGL);
    if (!window){
	printf("Error creating the window: %s \n", SDL_GetError());
	return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
	printf("Error creating the renderer: %s \n", SDL_GetError());
	return 0;
    }

    init_texture_modules();
    animation_rscs_init();
    load_textures(renderer);
    screen_init();
    return 1;
}

void terminate_sdl(){
    free_textures();
    terminate_texture_modules();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void render(float delta){
    screen_present(renderer, delta);
}
