#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/hgl_rand.h"

int
main( void ){
    hgl_rand_seed( time( NULL ) );
    const int num_to_guess = hgl_rand_int( -5, 5 );

    fprintf( stdout, "Secret number to guess %d\n", num_to_guess );
    
    return EXIT_SUCCESS;
}