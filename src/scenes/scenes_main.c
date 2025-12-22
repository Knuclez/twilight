#include <stdio.h>
#include "scenes/scenes_main.h"
#include "scenes/field_scene.h"
#include "interface/rendering/gui_entities.h"
#include "interface/screens_switch.h"

SceneType last_scene_type = -1;

//codigo temporal para hacer la lista de ids

void load_ecs(SceneType n_type){
    switch(n_type){
	case FIELD_SCENE:
	    field_scene_load_ecs();
	    break;
    }
    //maybe will need a load screen??
    switch_gui_entities_loading(n_type);
    return;
}

void unload_ecs(){
    unload_scene_gui_entities();
    return;
}

void initialize_scene(Scene *scene, SceneType n_type){
    scene->type = n_type;
    unload_ecs();
    load_ecs(n_type);
    return;
}

void finalize_scene(Scene *scene){
    switch(scene->type){
	case FIELD_SCENE:
	   break;
    }
}

//PUBLICS
void change_scene(Scene *scene, SceneType new_type){
    initialize_scene(scene, new_type);
}

void start_scenes(Scene *scene){
    initialize_scene(scene, FIELD_SCENE);
}
