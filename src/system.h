#ifndef H_SYSTEM
#define H_SYSTEM

#include "c99defs.h"
#include "entity.h"
#include "timing.h"
#include "vector.h"

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

typedef enum {
    ES_STARTUP,
    ES_PLAY,
    ES_QUIT
} engine_state_t;

typedef struct engine_s {
    int32_t adapter_index;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int32_t scr_width, scr_height;
    rect_t scr_bounds;
    vec2i_t mouse_pos;

    float target_fps;
    double target_frametime;
    int32_t frame_count;

    engine_state_t state;

    entity_t* ent_list;
} engine_t;

extern engine_t* engine;

bool sys_init(engine_t* eng);
void sys_refresh(engine_t* eng);
void sys_shutdown(engine_t* eng);

#endif