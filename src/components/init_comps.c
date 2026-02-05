#include "components/init_comps.h"

#include "components/animation_rsc_index.h"
#include "components/position_comp.h"
#include "components/size_comp.h"
#include "components/physical_bounds_comp.h"
#include "components/direction_comp.h"
#include "components/direction_vec_comp.h"
#include "components/sprite_source_comp.h"
#include "components/entity_bitmasks.h"

void init_components(){
    entity_bitmasks_init();
    position_component_list_init();
    size_component_list_init();
    physical_bounds_component_list_init();
    sprite_source_component_list_init();
    direction_component_list_init();
    direction_vec_component_list_init();
    animation_rsc_index_component_list_init();
} 
