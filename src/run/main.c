#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/random/hgl_rand.h"
#include "core/string/hgl_str.h"
#include "core/console/hgl_input.h"


int
main( void ){
    hgl_rand_seed( time( NULL ) );
    const int num_to_guess = hgl_rand_int( -5, 5 );

    fprintf( stdout, "Secret number to guess %d\n", num_to_guess );


    const hgl_str enter_num_txt = hgl_str_new( "Enter a number: ");
    fprintf( stdout, "%s", enter_num_txt.p_chars );

   

    hgl_input user_input = hgl_input_fetch( 256 );
    if( user_input.is_valid ) {
        hgl_str_int guess = hgl_str_parse_int( user_input.result );

        if( guess.is_valid ) {
            fprintf( stdout, "\nGuess: %d\n", guess.result );
        } else {
           fprintf( stderr, "\nInvalid\n" );
        }
    }


    return EXIT_SUCCESS;
}