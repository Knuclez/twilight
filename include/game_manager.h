#ifndef GAME_MANAGER_H
#define GAME_MANAGER_G

void initialize_game_systems();
void update(int current_time, float delta);

/* system tick functions */
void tick_lifetimes();
void tick_animations(float delta_time);

#endif
