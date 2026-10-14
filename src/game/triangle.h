#ifndef SK_TRIANGLE
#define SK_TRIANGLE

#include "shader_api/renderable_obj.h"
#include "shader_api/shader_api.h"

typedef struct sk_triangle_system_t {
    sk_renderable_obj_id_t triangle1, triangle2;
    sk_shader_id_t shader1, shader2;
    int triangle;
} sk_triangle_system_t;

void init_triangle_system();
void update_triangles();

#endif // SK_TRIANGLE