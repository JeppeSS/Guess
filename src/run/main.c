#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/random/hgl_rand.h"
#include "core/string/hgl_str.h"


int
main( void ){
    hgl_rand_seed( time( NULL ) );
    const int num_to_guess = hgl_rand_int( -5, 5 );

    fprintf( stdout, "Secret number to guess %d\n", num_to_guess );


    const hgl_str enter_num_txt = hgl_str_new( "Enter a number: ");
    fprintf( stdout, "%s", enter_num_txt.p_chars );

    char input[ 256 ] = { 0 };
    if( !fgets( input, sizeof( input ), stdin) ) {
        fprintf( stderr, "Something went wrong. Could not read user input." );
        return EXIT_FAILURE;
    }

    fprintf( stdout, "\nUser input: %s\n", input );

    return EXIT_SUCCESS;
}