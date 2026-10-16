#include "render_cmd_system.h"

static sk_render_cmd_system_t render_cmd_system;

void render_cmd_system_new_frame() {
    for (int i = 0; i < render_cmd_system.num_render_jobs_in_cur_frame; i++) {
        free(render_cmd_system.render_jobs[i]);
        render_cmd_system.render_jobs[i] = NULL;
    }
    render_cmd_system.num_render_jobs_in_cur_frame = 0;
}

void submit_to_render_cmd_system(sk_render_job_t* render_obj) {
    sk_render_job_t* new_render_obj = (sk_render_job_t*)malloc(sizeof(sk_render_job_t));
    new_render_obj->shader_to_render = render_obj->shader_to_render;
    new_render_obj->obj_to_render = render_obj->obj_to_render;

    unsigned int idx = render_cmd_system.num_render_jobs_in_cur_frame;
    render_cmd_system.render_jobs[idx] = new_render_obj;
    render_cmd_system.num_render_jobs_in_cur_frame++;
}


void draw_via_render_cmd_system() {
    for (int i = 0; i < render_cmd_system.num_render_jobs_in_cur_frame; i++) {
        sk_bind_shader(render_cmd_system.render_jobs[i]->shader_to_render);
        sk_bind_renderable_obj(render_cmd_system.render_jobs[i]->obj_to_render);
        sk_draw_renderable_obj(render_cmd_system.render_jobs[i]->obj_to_render);
    }
}