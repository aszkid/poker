#include <stdio.h>
#include <stdbool.h>
#include "gfx.h"
#include "utils.h"

int main(int argc, char **argv)
{
    log_info("Hello world...");
    log_debug("Debugging...");
    if (gfx_init() != GFX_OK) {
        return 1;
    }
    
    gfx_loop();

    return 0;
}
