#include <stddef.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "interface/rendering/texturing.h"
#include "interface/rendering/render_main.h"

//definido en 2
SDL_Texture *textures[N_TEXTURES];
TTF_Font* ougkeh_font;
SDL_Color white = {255,255,255};
SDL_Color red = {255,0,0};


SDL_Texture* get_texture_by_index(int index){
    return textures[index];
}

SDL_Texture* instance_dynamic_text_texture(SDL_Renderer *renderer,char *s){
    SDL_Surface *dyn_sfc = TTF_RenderText_Solid(ougkeh_font, s, red);
    SDL_Texture *res = SDL_CreateTextureFromSurface(renderer, dyn_sfc);
    if (res == NULL){
	printf("fallo al hacer la texturea dinamica \n ");
	printf("%s \n", SDL_GetError());
    }
    SDL_FreeSurface(dyn_sfc);
    return res;
}

void load_img_texture(SDL_Renderer *renderer,int index,char* dir){
    SDL_Surface *sfc = IMG_Load(dir);
    if (sfc == NULL){
	printf("Error loading surface %s \n", dir);
	printf("%s \n", SDL_GetError());
	SDL_ClearError();
    }
    SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, sfc);
    textures[index] = tx;
    if ( tx == NULL){
	printf("Error creating texture %s \n", dir);
	printf("%s \n", SDL_GetError());
	SDL_ClearError();
    }
    SDL_FreeSurface(sfc);
    return;
}

void load_textures(SDL_Renderer *renderer){
    memset(textures, 0, N_TEXTURES * sizeof(SDL_Texture*));
    ougkeh_font = TTF_OpenFont("assets/oughek-font.otf", 40);
    if (!ougkeh_font) {
        printf("TTF_OpenFont failed: %s\n", TTF_GetError());
        return;
    }

    load_img_texture(renderer, 0, "assets/images/nubev0.png"); 
    load_img_texture(renderer, 1, "assets/images/vaca_frontv0.png"); 
    /*
    SDL_Surface *login_sfc = TTF_RenderText_Solid(arena_font, "Please login", white);
    SDL_Surface *msg_sfc = TTF_RenderText_Solid(arena_font, "Welcome", white);
    textures[0] = SDL_CreateTextureFromSurface(renderer, login_sfc);
    SDL_FreeSurface(login_sfc);
    textures[1] = SDL_CreateTextureFromSurface(renderer, msg_sfc);
    SDL_FreeSurface(msg_sfc);
    */

    return;
}

void free_textures(){
    for(int i = 0; i < N_TEXTURES; i++){
	SDL_DestroyTexture(textures[i]);
	textures[i] = NULL;
    }
}

void init_texture_modules(){
    if (TTF_Init()==-1) {
	printf("Failed to TTF: %s", SDL_GetError());
	return;
    }

    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) && flags)) {
	printf("Failed to IMG: %s", SDL_GetError());
	return;
    }
}

void terminate_texture_modules(){
    IMG_Quit();
}
