#include "app_events.h"

key_events_t key_events;

void reset_key_events() {
    key_events.space_event.down_this_frame = 0;
    key_events.space_event.up = 0;
}

void register_key_event(SDL_Event event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE) {
        if (key_events.space_event.down == 0) {
            key_events.space_event.down_this_frame = 1;
        }
        key_events.space_event.down = 1;
        printf("space down");
    } else if (event.type == SDL_EVENT_KEY_UP && event.key.key == SDLK_SPACE) {
        key_events.space_event.down = 0;
        key_events.space_event.up = 1;
        printf("space up");
    }
}
