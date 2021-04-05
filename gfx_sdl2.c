// Implementation of the graphics subsystem using the SDL2 library
#include "gfx.h"
#include "utils.h"
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int gfx_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not initialize: %s\n", SDL_GetError());
        return GFX_ERROR;
    }

    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        log_error( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    
    return GFX_OK;
}

bool gfx_loop()
{
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            SDL_UpdateWindowSurface(window);
        }
    }
}