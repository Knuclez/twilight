#ifndef SCREEN_SWITCH_H
#define SCREEN_SWITCH_H

#include "scenes/scenes_main.h"

void screen_switch_mouse_button(int clicked_entity_id);
void screen_switch_keydown();
void screen_switch_keyup();
void screen_switch_input_event();
void switch_screen_rendering();
void switch_init_screen(SceneType s_type);
#endif
