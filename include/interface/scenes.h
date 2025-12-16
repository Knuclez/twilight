#ifndef SCENES_H
#define SCENES_H

typedef enum {FIELD_SCREEN} SceneType;

typedef union {
    SceneType type;
    void *data;
} Scene;

void initialize_scene(Scene *scene);
void finalize_scene(Scene *scene);
void scene_switch_mouse_button(int clicked_entity_id);
void scene_switch_keydown();
void scene_switch_input_event();
void switch_scene_rendering();

#endif
