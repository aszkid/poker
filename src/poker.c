#include <stdio.h>
#include <stdbool.h>
#include "gfx.h"
#include "utils.h"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

void main_loop()
{
    gfx_loop();
}

int main(int argc, char **argv)
{
    log_info("Hello world...");
    log_debug("Debugging...");
    log_error("An error!");
    for (int i = 0; i < 100; i++) {
        log_info("i=%d", i);
    }
    if (gfx_init() != GFX_OK) {
        return 1;
    }

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(main_loop, -1, 1);
#else
    do {
    } while (gfx_loop() != GFX_QUIT);
#endif

    return 0;
}
