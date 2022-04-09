#include <stdio.h>

#include "hgl_input.h"


hgl_input
hgl_input_fetch( size_t max_size ) {
    char input_buffer[ max_size ];
    if( !fgets( input_buffer, sizeof( input_buffer ), stdin) ) {
        return ( hgl_input ){ .result = hgl_str_null(), .is_valid = false };
    }

    return ( hgl_input ){ .result = hgl_str_new( input_buffer ), .is_valid = true };
}