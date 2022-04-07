#include <stdlib.h>

#include "hgl_rand.h"


void
hgl_rand_seed( unsigned int seed ) {
    srand( seed );
}

int
hgl_rand_int( int lower, int upper ) {
    return ( rand() % ( upper - lower + 1 ) ) + lower;
}