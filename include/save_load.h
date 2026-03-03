#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#define SAVE_FILE_PATH  "saves/twilight.sav"
#define SAVE_MAGIC      0x54574C47u   /* 'T','W','L','G' */
#define SAVE_VERSION    1

/* Serializa las entidades activas del GameState al archivo SAVE_FILE_PATH.
   Retorna 1 en exito, 0 en error. */
int entities_save();

/* Carga entidades desde SAVE_FILE_PATH y las restaura en el GameState.
   Retorna 1 en exito, 0 si el archivo no existe o es incompatible. */
int entities_load();

#endif
