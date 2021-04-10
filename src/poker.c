#include <stdio.h>
#include <stdbool.h>
#include "gfx.h"
#include "utils.h"
#include "net.h"
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
    if (gfx_init() != GFX_OK) {
        return 1;
    }

    if (net_init() != NET_OK) {
        log_error("Failed to initialize network subsystem");
        return 1;
    }

    net_connect("particles-dropped-ancient");

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(main_loop, -1, 1);
#else
    do {
    } while (gfx_loop() != GFX_QUIT);
#endif

    return 0;
}
