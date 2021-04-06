// Implementation of the graphics subsystem using the SDL2 library
#include "gfx.h"
#include "utils.h"
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int gfx_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log_error("SDL could not initialize: %s\n", SDL_GetError());
        return GFX_ERROR;
    }

    SDL_CreateWindowAndRenderer(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN,
        &window,
        &renderer
    );
    if (window == NULL || renderer == NULL) {
        log_error("SDL_Error: %s\n", SDL_GetError());
        return GFX_ERROR;
    }
    
    return GFX_OK;
}

int gfx_loop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
        switch (e.type) {
            case SDL_QUIT:
                return GFX_QUIT;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = { .x = 100, .y = 100, .w = 200, .h = 200 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    return GFX_OK;
}