#include <stdio.h>
#include <limits.h>

#include "hgl_input.h"


hgl_input
hgl_input_fetch( int max_size ) {
    if( max_size < 0 ) {
        return hgl_input_invalid();
    }

    char input_buffer[ max_size ];
    if( !fgets( input_buffer, max_size, stdin) ) {
        return hgl_input_invalid();
    }

    return ( hgl_input ){ .result = hgl_str_new( input_buffer ), .is_valid = true };
}