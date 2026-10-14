#include "app.h"

#include <stdio.h>
#include <math.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define GL_GLEXT_PROTOTYPES
#include <SDL3/SDL_opengl.h>

#include "app/app_events.h"
#include "game/game.h"
#include "shader_api/shader_api.h"
#include "shader_api/render_cmd_system.h"
#include "shader_api/renderable_obj.h"

int run(sk_app_t* app) {
    init(app);
    run_loop(app);
    return 0;
}

void init(sk_app_t* app) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Could not initialize SDL3 video", NULL);
        return;
	}

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    app->window = SDL_CreateWindow(
        "SDL3 OpenGL Example", 
        800, 600, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GLContext gl_context = SDL_GL_CreateContext(app->window);
    if (!gl_context) {
        printf("OpenGL Context creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
    }
}

void run_loop(sk_app_t* app) {
    app->running = true;

    float r = 0;
    float g = 0;
    float b = 0;

    struct timespec prev = {
        .tv_sec = 0,
        .tv_nsec = 0
    }; 

    game_init();

    while (app->running) {
        struct timespec cur;
        clock_gettime(CLOCK_MONOTONIC, &cur);

        float delta_time = 0;
        if (prev.tv_sec != 0 || prev.tv_nsec != 0) {
            delta_time = (cur.tv_sec - prev.tv_sec) + ((cur.tv_nsec - prev.tv_nsec) / ((float)1e9));
        }

        poll(app);

        render_cmd_system_new_frame();

        sk_shader_set_clear_color(fmod(r, 1.0f), fmod(g, 1.0f), fmod(b, 1.0f));
        sk_shader_clear();
        
        game_update();

        draw_via_render_cmd_system();

        SDL_GL_SwapWindow(app->window);

        prev = cur;
    }
}

void poll(sk_app_t* app) {

    reset_key_events();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            app->running = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN
                   || event.type == SDL_EVENT_KEY_UP) {
            register_key_event(event);
        } else if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
            sk_shader_set_viewport(event.window.data1, event.window.data2);
        }
    }
}