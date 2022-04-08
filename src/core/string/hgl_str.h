#ifndef _HGL_STR_
#define _HGL_STR_

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char *p_chars;
    size_t length;

} hgl_str;

#define hgl_str_null() ( hgl_str ){ NULL, 0 }

typedef struct {
    int  result;
    bool is_valid;

} hgl_str_int;

#define hgl_str_int_invalid() ( hgl_str_int ){ 0, false }

hgl_str 
hgl_str_new( char *p_chars );

bool
hgl_str_valid( hgl_str str );

bool
hgl_str_equal( hgl_str a, hgl_str b );

hgl_str_int
hgl_str_parse_int( hgl_str str );


#endif