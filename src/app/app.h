#ifndef SK_APP
#define SK_APP

#include <SDL3/SDL.h>

typedef struct sk_app_t {
    SDL_Window* window;
    bool running;
} sk_app_t;

void init(sk_app_t* app);
void run_loop(sk_app_t* app);
void poll(sk_app_t* app);

int run(sk_app_t* app);

#endif // SK_APP