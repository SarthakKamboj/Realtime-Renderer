#include "game.h"

#include "triangle.h"

void game_init() {
    init_triangle_system();
}

void game_update() {
    update_triangles();
}