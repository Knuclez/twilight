#include <stdio.h>
#include "scenes.h"
#include "interface/screens_switch.h"


SceneType last_scene_type = -1;


void initialize_scene(Scene *scene, SceneType n_type){
    scene->type = n_type;
    if(scene->type != 0){
	printf("fallo al inicializar la escena");
    }
    switch_gui_entities_loading(n_type);
    return;
}

void finalize_scene(Scene *scene){
    switch(scene->type){
	case FIELD_SCREEN:
	   break;
    }
}

//PUBLICS
void change_scene(Scene *scene, SceneType new_type){
    initialize_scene(scene, new_type);
}

void start_scenes(Scene *scene){
    initialize_scene(scene, FIELD_SCREEN);
}
