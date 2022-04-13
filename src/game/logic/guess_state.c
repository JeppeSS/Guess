#include "core/random/hgl_rand.h"

#include "guess_state.h"


guess_state
guess_state_new( uint8_t allowed_attempts ) {
    return ( guess_state ) {
        .number_to_guess  = hgl_rand_int( -10, 10 ),
        .allowed_attempts = allowed_attempts,
        .attempts_used    = 0
    };
}


guess_status
guess_state_make_guess( guess_state *p_state, int16_t guess ) {
    if( p_state->allowed_attempts == p_state->attempts_used ){
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