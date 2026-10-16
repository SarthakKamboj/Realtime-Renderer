#ifndef SK_APP_EVENTS
#define SK_APP_EVENTS

#include <SDL3/SDL.h>

typedef struct key_event_t {
    int down_this_frame;
    int down;
    int up;
} key_event_t;

typedef struct key_events_t {
    key_event_t space_event;
} key_events_t;

extern key_events_t key_events;

void reset_key_events();
void register_key_event(SDL_Event event);

#endif // SK_APP_EVENTS