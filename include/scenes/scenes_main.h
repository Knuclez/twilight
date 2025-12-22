#ifndef SCENES_H
#define SCENES_H

typedef enum {FIELD_SCENE} SceneType;

typedef union {
    SceneType type;
    void *data;
} Scene;

void start_scenes(Scene *scene);
void change_scene(Scene *new_scene, SceneType new_type);
#endif
