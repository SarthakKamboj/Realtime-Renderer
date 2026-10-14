#include "triangle.h"

#include "app/app_events.h"
#include "shader_api/render_cmd_system.h"

static sk_triangle_system_t triangle_system;

void init_triangle_system() {
    sk_renderable_vert_t vertices[4] = {
        { 0.5f,  0.5f, 0.0f } ,  // Top right (Index 0)
        { 0.5f, -0.5f, 0.0f },  // Bottom right (Index 1)
        { -0.5f, -0.5f, 0.0f },  // Bottom left (Index 2)
        { -0.5f,  0.5f, 0.0f }  // Top left (Index 3)
    };

    unsigned int indicies1[] = {  
        0, 1, 3,
    };
    unsigned int indicies2[] = {  
        1, 2, 3
    };

    sk_create_renderable_info_t triangle1_create_info;
    triangle1_create_info.verts = vertices;
    triangle1_create_info.num_verts = 4;
    triangle1_create_info.indicies = indicies1;
    triangle1_create_info.num_indicies = 3;

    sk_create_renderable_info_t triangle2_create_info;
    triangle2_create_info.verts = vertices;
    triangle2_create_info.num_verts = 4;
    triangle2_create_info.indicies = indicies2;
    triangle2_create_info.num_indicies = 3;

    triangle_system.triangle1 = sk_create_renderable_obj(&triangle1_create_info);
    triangle_system.triangle2 = sk_create_renderable_obj(&triangle2_create_info);

    triangle_system.shader1 = sk_create_shader(NULL, NULL);
    triangle_system.shader2 = sk_create_shader(NULL, NULL);

    triangle_system.triangle = 0;
}

void update_triangles() {
    if (key_events.space_event.down_this_frame == 1) {
        triangle_system.triangle = 1 - triangle_system.triangle;
    }

    sk_render_job_t render_job;
    if (triangle_system.triangle == 0) {
        render_job.shader_to_render = triangle_system.shader1;
        render_job.obj_to_render = triangle_system.triangle1;
    } else {
        render_job.shader_to_render = triangle_system.shader2;
        render_job.obj_to_render = triangle_system.triangle2;
    }
    submit_to_render_cmd_system(&render_job);
}