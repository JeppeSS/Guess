#ifndef _GUESSING_H_
#define _GUESSING_H_

#include <stdbool.h>
#include <stddef.h>

#include "core/string/hgl_str.h"
#include "logic/guess_state.h"

typedef enum {
    ENTER_NUM_TXT     = 0,
    INVALID_INPUT_TXT = 1,
    WIN_TXT           = 2,
    LOSE_TXT          = 3,
    HIGH_TXT          = 4,
    LOW_TXT           = 5,
    TXT_COUNT         = 6,

} txt_str;

typedef struct {  
    // Game loop
    bool is_running;

    // Game specific data
    guess_state state;

    // Configurations
    size_t max_input_size;
    
    // Storage
    hgl_str texts[ TXT_COUNT ];

} guessing;


guessing
guessing_new( void );

void
guessing_run( guessing *p_guessing );


#endif