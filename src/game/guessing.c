#include <stdio.h>
#include <time.h>

#include "guessing.h"

#include "core/random/hgl_rand.h"
#include "core/console/hgl_input.h"


static void
handle_menu_scene( guessing *p_guessing );

static game_state
fetch_menu_option( guessing *p_guessing );

static void
handle_play_scene( guessing *p_guessing );

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
        .game_state      = MENU,
        .texts           = {
            [ ENTER_NUM_TXT ]     = hgl_str_new( "Enter a number:" ),
            [ INVALID_INPUT_TXT ] = hgl_str_new( "Invalid input, try again." ),
            [ RANGE_TXT ]         = hgl_str_new( "Guess number between or equal: "),
            [ WIN_TXT ]           = hgl_str_new( "You win!" ),
            [ LOSE_TXT ]          = hgl_str_new( "You lost!" ),
            [ HIGH_TXT ]          = hgl_str_new( "Guess is too high!" ),
            [ LOW_TXT ]           = hgl_str_new( "Guess is too low!" ),
            [ MENU_TXT ]          = hgl_str_new( "Guessing Game\n\n1) Play\n2) Quit\n\n"),
            [ ATTEMPTS_TXT ]      = hgl_str_new( "Attmpts used:"),
            [ INPUT_MARKER_TXT ]  = hgl_str_new( "> " )
        }
    };
}

void
guessing_run( guessing *p_guessing ) {
    if( !p_guessing->is_running ) {
        p_guessing->state      = guess_state_select_difficulty( EASY );
        p_guessing->is_running = true;

        while( p_guessing->is_running ) {

            if( p_guessing->game_state == MENU ) {
                handle_menu_scene( p_guessing );

            } else if ( p_guessing->game_state == PLAY ) {
                handle_play_scene( p_guessing );

            } else {
                p_guessing->is_running = false;
            }

        } 
    }
}

static void
handle_menu_scene( guessing *p_guessing ) {
    const game_state state = fetch_menu_option( p_guessing );
    p_guessing->game_state = state;
}

static void
handle_play_scene( guessing *p_guessing ) {
    const hgl_str *p_texts = p_guessing->texts;
    fprintf( stdout, "\n%s %d - %d\n", p_texts[ RANGE_TXT ].p_chars, p_guessing->state.lower_bound, p_guessing->state.upper_bound );
    fprintf( stdout, "%s %d / %d\n", p_texts[ ATTEMPTS_TXT ].p_chars, p_guessing->state.attempts_used, p_guessing->state.allowed_attempts );
    const int guess = fetch_guess( p_guessing );
    process_guess( p_guessing, guess );
}


static game_state
fetch_menu_option( guessing *p_guessing ) {
    const hgl_str *p_texts = p_guessing->texts;

    game_state state = MENU;
    while ( state == MENU ) {
        fprintf( stdout, "%s", p_texts[ MENU_TXT ].p_chars );
        fprintf( stdout, "%s", p_texts[ INPUT_MARKER_TXT ].p_chars );

        const hgl_input user_input = hgl_input_fetch( p_guessing->max_input_size );

        if( user_input.is_valid ){
            const hgl_str_int option_parse = hgl_str_parse_int( user_input.result );
            if( option_parse.is_valid ) {
                int option = option_parse.result;
                if( option == 1 ) {
                    state = PLAY;
                } else if( option == 2 ){
                    state = QUIT;
                }
            }
        }

        if( state == MENU ){
            fprintf( stdout, "%s\n\n", p_texts[ INVALID_INPUT_TXT ].p_chars ); 
        }
    }
    
    return state;
}

static int
fetch_guess( guessing *p_guessing ) {
    const hgl_str *p_texts = p_guessing->texts;
    hgl_str_int guess = hgl_str_int_invalid();

    while( !guess.is_valid ){
        fprintf( stdout, "%s\n\n", p_texts[ ENTER_NUM_TXT ].p_chars );
        fprintf( stdout, "%s", p_texts[ INPUT_MARKER_TXT ].p_chars );
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
    const hgl_str *p_texts    = p_guessing->texts;
    const guess_status status = guess_state_make_guess( &p_guessing->state, guess );

    if( status == WIN_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ WIN_TXT ].p_chars );
        p_guessing->game_state = MENU;
    } else if( status == LOSE_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ LOSE_TXT ].p_chars );
        p_guessing->game_state = MENU;
    } else if( status == GUESS_HIGH_STATUS ) {
        fprintf( stdout, "%s\n\n", p_texts[ HIGH_TXT ].p_chars );
    } else {
        fprintf( stdout, "%s\n\n", p_texts[ LOW_TXT ].p_chars );
    }
}