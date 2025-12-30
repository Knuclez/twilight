#ifndef SCREEN_SWITCH_H
#define SCREEN_SWITCH_H


#include "scenes/scenes_main.h"

void scene_switch_mouse_button(int clicked_entity_id);
void scene_switch_keydown();
void scene_switch_input_event();
void switch_scene_rendering();
void switch_init_screen(SceneType s_type);
#endif
