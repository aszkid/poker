#include <stdio.h>
#include <stdbool.h>
#include "gfx.h"

int main(int argc, char **argv)
{
    if (gfx_init() != GFX_OK) {
        return 1;
    }
    
    gfx_loop();

    return 0;
}
