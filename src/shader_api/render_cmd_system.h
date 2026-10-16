#ifndef SK_RENDER_CMD_SYSTEM
#define SK_RENDER_CMD_SYSTEM

#include <stdlib.h>

#include "shader_api.h"
#include "renderable_obj.h"

typedef struct sk_render_job_t {
    sk_shader_id_t shader_to_render;
    sk_renderable_obj_id_t obj_to_render;
} sk_render_job_t;

typedef struct sk_render_cmd_system_t {
    sk_render_job_t* render_jobs[10];
    unsigned int num_render_jobs_in_cur_frame;
} sk_render_cmd_system_t;

void render_cmd_system_new_frame();
void submit_to_render_cmd_system(sk_render_job_t* render_obj);
void draw_via_render_cmd_system();

#endif // SK_RENDER_CMD_SYSTEM