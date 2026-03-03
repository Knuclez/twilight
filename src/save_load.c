#include <stdio.h>
#include <stdint.h>

#include "save_load.h"
#include "game_state.h"
#include "entities.h"

/* -----------------------------------------------------------------------
   Formato del archivo binario:
     [SaveHeader]         magic + version + max_index + player_key + count
     [Entity] x count     solo entidades activas (key.index != 0)
   ----------------------------------------------------------------------- */

typedef struct {
    uint32_t  magic;
    uint16_t  version;
    int       max_index;
    EntityKey player_key;
    int       entity_count;
} SaveHeader;


int entities_save(){
    GameState *gs = get_game_state_p();

    /* contar entidades activas */
    int count = 0;
    for (int i = 0; i < gs->max_index; i++){
        if (gs->entities[i].key.index != 0) count++;
    }

    FILE *f = fopen(SAVE_FILE_PATH, "wb");
    if (!f){
        printf("[save] Error abriendo %s para escritura\n", SAVE_FILE_PATH);
        return 0;
    }

    SaveHeader header = {
        .magic        = SAVE_MAGIC,
        .version      = SAVE_VERSION,
        .max_index    = gs->max_index,
        .player_key   = gs->player_key,
        .entity_count = count,
    };
    fwrite(&header, sizeof(SaveHeader), 1, f);

    for (int i = 0; i < gs->max_index; i++){
        if (gs->entities[i].key.index == 0) continue;
        fwrite(&gs->entities[i], sizeof(Entity), 1, f);
    }

    fclose(f);
    printf("[save] %d entidades guardadas en %s\n", count, SAVE_FILE_PATH);
    return 1;
}


int entities_load(){
    FILE *f = fopen(SAVE_FILE_PATH, "rb");
    if (!f){
        printf("[load] No se encontro archivo de guardado (%s)\n", SAVE_FILE_PATH);
        return 0;
    }

    SaveHeader header;
    if (fread(&header, sizeof(SaveHeader), 1, f) != 1){
        printf("[load] Error leyendo header\n");
        fclose(f);
        return 0;
    }

    if (header.magic != SAVE_MAGIC){
        printf("[load] Archivo invalido (magic incorrecto)\n");
        fclose(f);
        return 0;
    }
    if (header.version != SAVE_VERSION){
        printf("[load] Version incompatible: esperaba %d, encontro %d\n",
               SAVE_VERSION, header.version);
        fclose(f);
        return 0;
    }

    GameState *gs = get_game_state_p();

    /* limpiar el array antes de restaurar */
    entities_list_init();

    for (int i = 0; i < header.entity_count; i++){
        Entity ent;
        if (fread(&ent, sizeof(Entity), 1, f) != 1){
            printf("[load] Error leyendo entidad %d\n", i);
            fclose(f);
            return 0;
        }
        /* restaurar en la posicion original por indice */
        int idx = ent.key.index;
        if (idx > 0 && idx < MAX_ENTITIES){
            gs->entities[idx] = ent;
        }
    }

    gs->max_index  = header.max_index;
    gs->player_key = header.player_key;

    fclose(f);
    printf("[load] %d entidades cargadas desde %s\n", header.entity_count, SAVE_FILE_PATH);
    return 1;
}
