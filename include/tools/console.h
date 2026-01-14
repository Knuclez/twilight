#ifndef CONSOLE_H
#define CONSOLE_H

typedef enum {SPAWN} ComandActionType;

typedef struct {
    int id;
    int bitmask;
} Command;

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;


void console_init();
void interpret_command(const char *s, int size);

#endif
