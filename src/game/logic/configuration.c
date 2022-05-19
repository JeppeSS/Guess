#include "configuration.h"



configuration
configuration_new( void ) {
    return ( configuration ){ .max_input_size = 64 };
}