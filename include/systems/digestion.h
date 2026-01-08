#ifndef DIGESTION_SYS_H
#define DIGESTION_SYS_H

#define MAX_TIME 10

typedef struct {
   int animal_id;
   struct DigestionNode* previous_node;
} DigestionNode;



void init_digestion_system();
void start_digestion(int cow_id);
void tick_digestion_system();
#endif

