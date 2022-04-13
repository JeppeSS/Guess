#include <stdio.h>
#include <time.h>

#include "guessing.h"

#include "core/random/hgl_rand.h"
#include "core/console/hgl_input.h"

typedef enum {
    HIGH,
    LOW,
    EQUAL,

} guess_status;

guess_status
process_guess( int number_to_guess, int guess );



guessing
guessing_new( unsigned int allowed_attempts ) {
    hgl_rand_seed( time( NULL ) );

    return ( guessing ) {
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0,
        .number_to_guess = hgl_rand_int( 0, 10 ),
        .max_input_size  = 64,
        .texts           = {
            [ ENTER_NUM_TXT ]     = hgl_str_new( "Enter a number:" ),
            [ INVALID_INPUT_TXT ] = hgl_str_new( "Invalid input, try again." ),
            [ WIN_TXT ]           = hgl_str_new( "You win!" ),
            [ HIGH_TXT ]          = hgl_str_new( "Guess is too high!" ),
            [ LOW_TXT ]           = hgl_str_new( "Guess is too low!" )

        }
    };
}

void
guessing_update( guessing *p_guess ) {
        hgl_str *p_texts = p_guess->texts;
        fprintf( stdout, "%s ", p_texts[ ENTER_NUM_TXT ].p_chars );
        const hgl_input user_input = hgl_input_fetch( p_guess->max_input_size );

        if( user_input.is_valid ) {
            const hgl_str_int guess_input = hgl_str_parse_int( user_input.result );
            if( guess_input.is_valid ) {
                const guess_status status = process_guess( p_guess->number_to_guess, guess_input.result );
                if( status == EQUAL ) {
                    fprintf( stdout, "%s\n\n", p_texts[ WIN_TXT ].p_chars );
                } else if ( status == HIGH ) {
                    fprintf( stdout, "%s\n\n", p_texts[ HIGH_TXT ].p_chars );
                    p_guess->attempts_used++;
                } else {
                    fprintf( stdout, "%s\n\n", p_texts[ LOW_TXT ].p_chars );
                    p_guess->attempts_used++;
                }

            } else {
                fprintf( stdout, "%s\n\n", p_texts[ INVALID_INPUT_TXT ].p_chars ); 
            }

        } else {
            fprintf( stdout, "%s\n\n", p_texts[ INVALID_INPUT_TXT ].p_chars );
        }
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