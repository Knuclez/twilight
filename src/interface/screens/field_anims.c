#include "interface/screens/field_anims.h"
#include "interface/rendering/gui_entities.h"

void animate_clouds(float delta){
    GUI_Entity *cloud = get_entity_by_id(101);
    SDL_Rect *rect = &cloud->rect;
    rect->x += (50 * delta);
}

