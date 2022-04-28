#include <stdio.h>
#include <time.h>

#include "guessing.h"

#include "core/random/hgl_rand.h"
#include "core/console/hgl_input.h"

static int
fetch_guess( guessing *p_guessing );

static void
process_guess( guessing *p_guessing, int guess );

guessing
guessing_new( void ) {
    hgl_rand_seed( time( NULL ) );

    return ( guessing ) {
        .is_running      = false,
        .max_input_size  = 64,
        .texts           = {
            [ ENTER_NUM_TXT ]     = hgl_str_new( "Enter a number:" ),
            [ INVALID_INPUT_TXT ] = hgl_str_new( "Invalid input, try again." ),
            [ WIN_TXT ]           = hgl_str_new( "You win!" ),
            [ LOSE_TXT ]          = hgl_str_new( "You lost!" ),
            [ HIGH_TXT ]          = hgl_str_new( "Guess is too high!" ),
            [ LOW_TXT ]           = hgl_str_new( "Guess is too low!" )

        }
    };
}

void
guessing_run( guessing *p_guessing ) {
    if( !p_guessing->is_running ) {
        p_guessing->state      = guess_state_new( -10, 10, 3 );
        p_guessing->is_running = true;
            
        while( p_guessing->is_running ) {
            int guess = fetch_guess( p_guessing );
            process_guess( p_guessing, guess );
        }
    }
}


static int
fetch_guess( guessing *p_guessing ) {
    const hgl_str *p_texts = p_guessing->texts;
    hgl_str_int guess = hgl_str_int_invalid();


    while( !guess.is_valid ){
        fprintf( stdout, "%s ", p_texts[ ENTER_NUM_TXT ].p_chars );
        const hgl_input user_input = hgl_input_fetch( p_guessing->max_input_size );
        if( user_input.is_valid ){
            guess = hgl_str_parse_int( user_input.result );
        }

        if( !guess.is_valid ) {
            fprintf( stdout, "%s\n\n", p_texts[ INVALID_INPUT_TXT ].p_chars ); 
        }
    }

    return guess.result;
}

static void
process_guess( guessing *p_guessing, int guess ) {
    const hgl_str *p_texts = p_guessing->texts;
    const guess_status status = guess_state_make_guess( &p_guessing->state, guess );

    if( status == WIN_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ WIN_TXT ].p_chars );
        p_guessing->is_running = false;
    } else if( status == LOSE_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ LOSE_TXT ].p_chars );
        p_guessing->is_running = false;
    } else if( status == GUESS_HIGH_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ HIGH_TXT ].p_chars );
    } else {
        fprintf( stdout, "%s\n\n", p_texts[ LOW_TXT ].p_chars );
    }
}