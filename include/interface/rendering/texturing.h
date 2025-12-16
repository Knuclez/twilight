#ifndef TEXTURING_H
#define TEXTURING_H
#include <SDL2/SDL.h>


#define N_TEXTURES 2

void init_texture_modules();
void terminate_texture_modules();
void load_textures(SDL_Renderer *renderer);
void free_textures();
SDL_Texture* get_texture_by_index(int index);
SDL_Texture* instance_dynamic_text_texture(SDL_Renderer *renderer,char *s);

#endif
