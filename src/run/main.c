#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/random/hgl_rand.h"
#include "core/string/hgl_str.h"
#include "core/console/hgl_input.h"

typedef struct {
    int number_to_guess;
    unsigned int allowed_attempts;
    unsigned int attempts_used;

} guess_state;

guess_state
guess_state_new( unsigned int allowed_attempts );

int
main( void ){
    // Initialize
    hgl_rand_seed( time( NULL ) );
    guess_state game = guess_state_new( 3 );

    const size_t MAX_INPUT_SIZE = 128;

    // Text
    const hgl_str enter_num_txt     = hgl_str_new( "Enter a number:" );
    const hgl_str invalid_input_txt = hgl_str_new( "Invalid input, try again." ); 
    const hgl_str win_txt           = hgl_str_new( "You win!");


    bool is_running = true;
    while( is_running ) {
        fprintf( stdout, "%s ", enter_num_txt.p_chars );
        const hgl_input user_input = hgl_input_fetch( MAX_INPUT_SIZE );

        if( user_input.is_valid ) {
            const hgl_str_int guess_input = hgl_str_parse_int( user_input.result );
            if( guess_input.is_valid ) {
                const int guess = guess_input.result;
                if( guess == game.number_to_guess ) {
                    fprintf( stdout, "%s\n", win_txt.p_chars );
                    is_running = false;
                }
            } else {
                fprintf( stdout, "%s\n\n", invalid_input_txt.p_chars ); 
            }

        } else {
            fprintf( stdout, "%s\n\n", invalid_input_txt.p_chars );
        }

    }



    return EXIT_SUCCESS;
}

guess_state
guess_state_new( unsigned int allowed_attempts ) {
    return ( guess_state ) {
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0,
        .number_to_guess = hgl_rand_int( 0, 10 )
    };
}

