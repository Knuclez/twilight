#include "components/init_comps.h"

#include "components/texture_indx_comp.h"
#include "components/position_comp.h"
#include "components/direction_comp.h"

void init_components(){
   position_component_list_init();
   //texture_index_component_list_init();
   direction_component_list_init();
}
