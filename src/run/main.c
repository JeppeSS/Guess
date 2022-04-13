#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/guessing.h"


int
main( void ){
    guessing game = guessing_new( 3 );

    bool is_running = true;
    while( is_running ) {
        guessing_update( &game );
    }


    return EXIT_SUCCESS;
}



