#include "main.h"
#include "font.h"
#include "system.h"
#include "input.h"
#include "command.h"
//#include "timing.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)
engine_t* engine = NULL;
int32_t mouse_x, mouse_y; // extern

bool sys_init(engine_t* eng)
{
    double init_start = timing_getsec();
    eng->frame_count = 0;

    SDL_Init(SDL_FLAGS);
    eng->window = SDL_CreateWindow
    (
        "bulletmind",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        eng->scr_width, eng->scr_height,
        SDL_WINDOW_SHOWN
    );

    if(eng->window == NULL) {
        printf("sys_window: %s\n", SDL_GetError());
        return false;
    }

    eng->renderer = SDL_CreateRenderer(eng->window, eng->adapter_index, SDL_RENDERER_ACCELERATED);
    if (eng->renderer == NULL) {
        printf("sys_renderer: %s\n", SDL_GetError());
        return false;
    }

    in_init();
    cmd_init();
    ent_init(&eng->ent_list, MAX_ENTITIES);
    timing_init();
    font_init(eng->renderer, "font_7px.tga");

    recti32_t scr = { 0, 0, eng->scr_width, eng->scr_height };
    eng->scr_bounds = scr;
    eng->target_frametime = TARGET_FRAMETIME(eng->target_fps);
    eng->state = ES_STARTUP;

    printf("sys_init OK [%fms]\n", (timing_getsec() - init_start) * 1000.0);

    return true;
}

void sys_refresh()
{
    SDL_Event e;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_KEYDOWN:
                in_setkeystate(e.key.keysym.scancode, KEY_DOWN);
                break;
            case SDL_KEYUP:
                in_setkeystate(e.key.keysym.scancode, KEY_UP);
                break;
            case SDL_MOUSEBUTTONDOWN:
                //printf("%d\n", SDL_BUTTON(e.button.button));
                in_setmousebuttonstate((e.button.button), e.button.state);
                break;
            case SDL_MOUSEBUTTONUP:
                in_setmousebuttonstate((e.button.button), e.button.state);
                break;
        }
    }
}

void sys_shutdown(engine_t* eng)
{
    ent_shutdown(&eng->ent_list);
    cmd_shutdown();
    in_shutdown();

    SDL_DestroyRenderer(eng->renderer);
    SDL_DestroyWindow(eng->window);
    eng->renderer = NULL;
    eng->window = NULL;
    SDL_Quit();
    printf("sys_shutdown OK\n\nGoodbye!\n");
}