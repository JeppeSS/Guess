#ifndef _HGL_INPUT_H_
#define _HGL_INPUT_H_

#include <stdbool.h>

#include "core/string/hgl_str.h"

typedef struct {
    hgl_str result;
    bool    is_valid;

} hgl_input;

#define hgl_input_invalid() ( hgl_input ){ hgl_str_null(), false }

hgl_input
hgl_input_fetch( size_t max_size );

#endif