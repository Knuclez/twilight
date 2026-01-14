#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools/console.h"
//CODE FROM STACKOVERFLOW !!!!!!!
//
//
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

/* Convert string s to int out.
 *
 * @param[out] out The converted int. Cannot be NULL.
 *
 * @param[in] s Input string to be converted.
 *
 *     The format is the same as strtol,
 *     except that the following are inconvertible:
 *
 *     - empty string
 *     - leading whitespace
 *     - any trailing characters that are not part of the number
 *
 *     Cannot be NULL.
 *
 * @param[in] base Base to interpret string in. Same range as strtol (2 to 36).
 *
 * @return Indicates if the operation succeeded, or why it failed.
 */

str2int_errno str2int(int *out, char *s, int base) {
    char *end;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2INT_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2INT_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2INT_UNDERFLOW;
    if (*end != '\0')
        return STR2INT_INCONVERTIBLE;
    *out = l;
    return STR2INT_SUCCESS;
}

//
//
//FINISHES HERE   !!!!!!!!!


int last_id_console;

void free_words_space(char **words_p, int word_count){
    for(int i = 0; i < word_count; i++){
	free(*(words_p+i));
    }
    free(words_p);
}

void command_create(Command *com ,char **words_p, int word_count){
    last_id_console += 1;
    int mask_int;
    str2int(&mask_int, words_p[0], 10);
    com->id = last_id_console;
    com->bitmask = mask_int;
    printf("%.2x bitmask \n", com->bitmask);
    free_words_space(words_p, word_count);
}


void interpret_command(const char *csv, int len){
    //esto podria ser una sola locacion, ya que si conozco el algebra
    //de los punteros, solo tengo que agarrar la capacidad de word_amount * word_size
    //y usar ese espacio, con algebra de punteros?

    int word_amount = sizeof(char*) * 10;
    char **words_p = malloc(word_amount);
   
    int word_size = sizeof(char) * 10;
    char *current_word = malloc(word_size); 

    if(len >= (word_amount * word_size)){
	free(words_p);
	free(current_word);
	printf("comand is to long \n");
	return;
    }

    int word_count = 0;
    int word_first_char_index = 0;

    //fill words_p
    for(int i =0; i < len ; i++){
	printf("i: %.X\n",i);
	char c = *(csv + i); 
	int internal_pos = i - word_first_char_index;

	if(c == ',' || i == len - 1){
	    //process word and start next
	    *(current_word + internal_pos) = '\0';
	    *(words_p + word_count) = current_word;

	    word_first_char_index = i + 1;
	    word_count += 1;
	    printf("word: %s \n", current_word);
	    current_word = malloc(word_size);
	    continue;
	}
	*(current_word + internal_pos) = c;
    } 

    free(current_word);

    Command new_command;
    command_create(&new_command, words_p, word_count);
   
}

void console_init(){
    last_id_console = 0;
    return;
}

