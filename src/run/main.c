#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "core/random/hgl_rand.h"
#include "core/string/hgl_str.h"
#include "core/console/hgl_input.h"


typedef enum {
    ENTER_NUM_TXT     = 0,
    INVALID_INPUT_TXT = 1,
    WIN_TXT           = 2,
    HIGH_TXT          = 3,
    LOW_TXT           = 4,
    TXT_COUNT         = 5,

} txt_str;

typedef struct {
    int number_to_guess;
    unsigned int allowed_attempts;
    unsigned int attempts_used;
    hgl_str texts[ TXT_COUNT ];

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

    bool is_running = true;
    while( is_running ) {
        fprintf( stdout, "%s ", game.texts[ ENTER_NUM_TXT ].p_chars );
        const hgl_input user_input = hgl_input_fetch( MAX_INPUT_SIZE );

        if( user_input.is_valid ) {
            const hgl_str_int guess_input = hgl_str_parse_int( user_input.result );
            if( guess_input.is_valid ) {
                const guess_status status = process_guess( game.number_to_guess, guess_input.result );
                if( status == EQUAL ) {
                    fprintf( stdout, "%s\n\n", game.texts[ WIN_TXT ].p_chars );
                    is_running = false;
                } else if ( status == HIGH ) {
                    fprintf( stdout, "%s\n\n", game.texts[ HIGH_TXT ].p_chars );
                    game.attempts_used++;
                } else {
                    fprintf( stdout, "%s\n\n", game.texts[ LOW_TXT ].p_chars );
                    game.attempts_used++;
                }

            } else {
                fprintf( stdout, "%s\n\n", game.texts[ INVALID_INPUT_TXT ].p_chars ); 
            }

        } else {
            fprintf( stdout, "%s\n\n", game.texts[ INVALID_INPUT_TXT ].p_chars );
        }

    }



    return EXIT_SUCCESS;
}

game_state
game_state_new( unsigned int allowed_attempts ) {
    return ( game_state ) {
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0,
        .number_to_guess = hgl_rand_int( 0, 10 ),
        .texts           = {
            [ ENTER_NUM_TXT ]     = hgl_str_new( "Enter a number:" ),
            [ INVALID_INPUT_TXT ] = hgl_str_new( "Invalid input, try again." ),
            [ WIN_TXT ]           = hgl_str_new( "You win!" ),
            [ HIGH_TXT ]          = hgl_str_new( "Guess is too high!" ),
            [ LOW_TXT ]           = hgl_str_new( "Guess is too low!" )

        }
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

