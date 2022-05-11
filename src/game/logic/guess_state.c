#include "core/random/hgl_rand.h"

#include "guess_state.h"

static guess_state
guess_state_new( int16_t lower_bound, int16_t upper_bound, uint8_t allowed_attempts );


guess_state
guess_state_select_difficulty( guess_difficulty difficulty ) {
    switch ( difficulty ) {
        case EASY:
            return guess_state_new( 0, 10, 4 );
        case MEDIUM:
            return guess_state_new( 0, 100, 8 );
        case HARD:
            return guess_state_new( -100, 100, 10 );
        case HARDCORE:
            return guess_state_new( -1000, 1000, 5 );
        default:
            return guess_state_new( 0, 10, 4 );
    }
}


guess_status
guess_state_make_guess( guess_state *p_state, int16_t guess ) {
    if( ( p_state->allowed_attempts - 1 ) == p_state->attempts_used ){
        return LOSE_STATUS;
    } else { 
        p_state->attempts_used++;
    }

    const int16_t number_to_guess = p_state->number_to_guess;
    if( guess == number_to_guess ) {
        return WIN_STATUS;
    } else if ( guess > number_to_guess ) {
        return GUESS_HIGH_STATUS;
    } else {
        return GUESS_LOW_STATUS;
    }
}

static guess_state
guess_state_new( int16_t lower_bound, int16_t upper_bound, uint8_t allowed_attempts ) {
    return ( guess_state ) {
        .lower_bound      = lower_bound,
        .upper_bound      = upper_bound,
        .number_to_guess  = hgl_rand_int( lower_bound, upper_bound ),
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0
    };
}