#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/guessing.h"


int
main( void ){
    guessing game = guessing_new();
    guessing_run( &game );

    return EXIT_SUCCESS;
}



