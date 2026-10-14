#ifndef SK_RENDERBALE_OBJ
#define SK_RENDERBALE_OBJ

typedef unsigned int sk_renderable_obj_id_t;

typedef struct sk_renderable_vert_t {
    float x_pos, y_pos, z_pos;
} sk_renderable_vert_t;

typedef struct sk_renderable_obj_t {
    sk_renderable_obj_id_t id;
    unsigned int vao, vbo, ebo;
    unsigned int num_indicies;
    unsigned int num_verts;
} sk_renderable_obj_t;

typedef struct sk_create_renderable_info_t {
    sk_renderable_vert_t* verts;
    unsigned int num_verts;
    unsigned int* indicies;
    unsigned int num_indicies;
} sk_create_renderable_info_t;

sk_renderable_obj_id_t sk_create_renderable_obj(sk_create_renderable_info_t* create_info);
void sk_bind_renderable_obj(sk_renderable_obj_id_t id);
void sk_draw_renderable_obj(sk_renderable_obj_id_t id);

#endif // SK_RENDERBALE_OBJ