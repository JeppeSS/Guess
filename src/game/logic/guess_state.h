#ifndef _GUESS_STATE_H_
#define _GUESS_STATE_H_

#include <stdint.h>

typedef enum {
    WIN_STATUS,
    LOSE_STATUS,
    GUESS_LOW_STATUS,
    GUESS_HIGH_STATUS

} guess_status;

typedef struct {
    int16_t number_to_guess;
    uint8_t allowed_attempts;
    uint8_t attempts_used;

} guess_state;


guess_state
guess_state_new( uint8_t allowed_attempts );

guess_status
guess_state_make_guess( guess_state *p_state, int16_t guess );


#endif