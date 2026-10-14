#include "renderable_obj.h"

#define GL_GLEXT_PROTOTYPES
#include <SDL3/SDL_opengl.h>

static sk_renderable_obj_t renderable_objs[10];

sk_renderable_obj_id_t sk_create_renderable_obj(sk_create_renderable_info_t* create_info) {

    static unsigned int running_id = 0; 

    sk_renderable_obj_t* obj = &renderable_objs[running_id];
    obj->id = running_id;
    running_id++;

    obj->num_verts = create_info->num_verts;
    obj->num_indicies = create_info->num_indicies;

    glGenVertexArrays(1, &obj->vao);
    glGenBuffers(1, &obj->vbo);
    glGenBuffers(1, &obj->ebo);

    glBindVertexArray(obj->vao);

    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sk_renderable_vert_t) * create_info->num_verts, (float*)create_info->verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * create_info->num_indicies, create_info->indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return obj->id;
}

void sk_bind_renderable_obj(sk_renderable_obj_id_t id) {
    sk_renderable_obj_t* obj = &renderable_objs[id];
    glBindVertexArray(obj->vao); 
}

void sk_draw_renderable_obj(sk_renderable_obj_id_t id) {
    sk_renderable_obj_t* obj = &renderable_objs[id];
    glDrawElements(GL_TRIANGLES, obj->num_indicies, GL_UNSIGNED_INT, 0);
}