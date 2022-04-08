#include "hgl_str.h"

#include <stdio.h>

static size_t
get_length( char *p_chars );

static bool
is_digit( char value );

static int
char_to_int( char value );


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

hgl_str_int
hgl_str_parse_int( hgl_str str ) {
    if( !hgl_str_valid( str ) ) {
        return hgl_str_int_invalid();
    }

    
    int start_idx = 0;
    int sign = 1;
    if( str.p_chars[ 0 ] == '-' ) {
        sign = -1;
        start_idx = 1;
    }

   
    int result = 0;
    for( size_t i = start_idx; i < str.length; i++ ) {
        if( !is_digit( str.p_chars[ i ] ) ) {
            return hgl_str_int_invalid();
        }

        result = result * 10 + char_to_int( str.p_chars[ i ] );
    }

    return ( hgl_str_int ){ sign * result, true };
    
}


static size_t
get_length( char *p_chars ) {
    size_t length = 0;
    while( p_chars[ length ] != '\0') {
        length++;
    }

    return length > 0 ? length - 1 : 0;
}

static bool
is_digit( char value ) {
    return value >= '0' && value <= '9';
}

static int
char_to_int( char value ) { 
    return value - '0';
}

