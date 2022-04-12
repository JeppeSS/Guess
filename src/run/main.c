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

} game_state;

typedef enum {
    HIGH,
    LOW,
    EQUAL,

} guess_status;

game_state
game_state_new( unsigned int allowed_attempts );

guess_status
process_guess( int number_to_guess, int guess );


int
main( void ){
    // Initialize
    hgl_rand_seed( time( NULL ) );
    game_state game = game_state_new( 3 );

    const size_t MAX_INPUT_SIZE = 128;

    // Text
    const hgl_str enter_num_txt     = hgl_str_new( "Enter a number:" );
    const hgl_str invalid_input_txt = hgl_str_new( "Invalid input, try again." ); 
    const hgl_str win_txt           = hgl_str_new( "You win!");
    const hgl_str too_high_txt      = hgl_str_new( "Guess is too high!" );
    const hgl_str too_low_txt       = hgl_str_new( "Guess is too low!" );


    bool is_running = true;
    while( is_running ) {
        fprintf( stdout, "%s ", enter_num_txt.p_chars );
        const hgl_input user_input = hgl_input_fetch( MAX_INPUT_SIZE );

        if( user_input.is_valid ) {
            const hgl_str_int guess_input = hgl_str_parse_int( user_input.result );
            if( guess_input.is_valid ) {
                const guess_status status = process_guess( game.number_to_guess, guess_input.result );
                if( status == EQUAL ) {
                    fprintf( stdout, "%s\n\n", win_txt.p_chars );
                    is_running = false;
                } else if ( status == HIGH ) {
                    fprintf( stdout, "%s\n\n", too_high_txt.p_chars );
                    game.attempts_used++;
                } else {
                    fprintf( stdout, "%s\n\n", too_low_txt.p_chars );
                    game.attempts_used++;
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

game_state
game_state_new( unsigned int allowed_attempts ) {
    return ( game_state ) {
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0,
        .number_to_guess = hgl_rand_int( 0, 10 )
    };
}


guess_status
process_guess( int number_to_guess, int guess ) {
    if( guess > number_to_guess ) {
        return HIGH;
    } else if ( guess < number_to_guess ) {
        return LOW;
    }

    return EQUAL;
}

