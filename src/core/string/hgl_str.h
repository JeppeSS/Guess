#ifndef _HGL_STR_
#define _HGL_STR_

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char *p_chars;
    size_t length;

} hgl_str;

#define hgl_str_null() ( hgl_str ){ NULL, 0 }

hgl_str 
hgl_str_new( char *p_chars );

bool
hgl_str_valid( hgl_str str );

bool
hgl_str_equal( hgl_str a, hgl_str b );

#endif