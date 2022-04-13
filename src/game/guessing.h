#ifndef _GUESSING_H_
#define _GUESSING_H_

#include <stddef.h>

#include "core/string/hgl_str.h"

typedef enum {
    ENTER_NUM_TXT     = 0,
    INVALID_INPUT_TXT = 1,
    WIN_TXT           = 2,
    HIGH_TXT          = 3,
    LOW_TXT           = 4,
    TXT_COUNT         = 5,

} txt_str;

typedef struct {  
    // Game specific data
    int number_to_guess;
    unsigned int allowed_attempts;
    unsigned int attempts_used;

    // Configurations
    size_t max_input_size;
    
    // Storage
    hgl_str texts[ TXT_COUNT ];

} guessing;


guessing
guessing_new( unsigned int allowed_attempts );

void
guessing_update( guessing *p_guess );

#endif