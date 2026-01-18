#ifndef SCENES_H
#define SCENES_H

typedef enum {FIELD_SCENE} SceneType;

//esta data podria ser un bitmask y hacer algo como components tal vez
typedef union {
    SceneType type;
    void *data;
} Scene;

void start_scenes(Scene *scene);
void change_scene(Scene *new_scene, SceneType new_type);
#endif
