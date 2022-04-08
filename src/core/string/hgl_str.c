#include "hgl_str.h"

static size_t
get_length( char *p_chars );


hgl_str 
hgl_str_new( char *p_chars ) {
    if( !p_chars ){
        return hgl_str_null();
    }

    const size_t length = get_length( p_chars );
    return ( hgl_str ) { .p_chars = p_chars, .length = length };
}

bool
hgl_str_valid( hgl_str str ) {
    return str.p_chars != NULL;
}

bool
hgl_str_equal( hgl_str a, hgl_str b ) {
    if( !hgl_str_valid( a ) || !hgl_str_valid( b ) ) {
        return false;
    }

    if( a.length != b.length ){
        return false;
    }

    for( size_t i = 0; i < a.length; i++ ) {
        if( a.p_chars[ i ] != b.p_chars[ i ] ) {
            return false;
        }
    }

    return true;

}


static size_t
get_length( char *p_chars ) {
    size_t length = 0;
    while( p_chars[ length ] != '\0') {
        length++;
    }

    return length;
}

