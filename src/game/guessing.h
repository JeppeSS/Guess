#ifndef _GUESSING_H_
#define _GUESSING_H_

#include <stdbool.h>
#include <stddef.h>

#include "core/string/hgl_str.h"
#include "logic/guess_state.h"

typedef enum {
    ENTER_NUM_TXT       = 0,
    INVALID_INPUT_TXT   = 1,
    WIN_TXT             = 2,
    LOSE_TXT            = 3,
    HIGH_TXT            = 4,
    LOW_TXT             = 5,
    MENU_TXT            = 6,
    INPUT_MARKER_TXT    = 7,
    RANGE_TXT           = 8,
    ATTEMPTS_TXT        = 9,
    DIFFICULTY_MENU_TXT = 10,
    TXT_COUNT           = 11

} txt_str;


typedef enum {
    MENU,
    PLAY,
    QUIT

} game_state;

typedef struct {  
    // Game loop
    bool is_running;

    // Game specific data
    game_state  game_state;
    guess_state state;

    // Configurations
    int max_input_size;
    
    // Storage
    hgl_str texts[ TXT_COUNT ];

} guessing;


guessing
guessing_new( void );

void
guessing_run( guessing *p_guessing );


#endif