#ifndef SK_SHADER_API
#define SK_SHADER_API

#define GL_GLEXT_PROTOTYPES
#include <SDL3/SDL_opengl.h>

typedef unsigned int sk_shader_id_t;

typedef struct sk_shader_t {
    sk_shader_id_t id; 
    unsigned int shader_program;
} sk_shader_t;

sk_shader_id_t sk_create_shader(const char* vert_file_path, const char* frag_file_path);
void sk_bind_shader(sk_shader_id_t id);

void sk_shader_set_viewport(int width, int height);
void sk_shader_clear();
void sk_shader_set_clear_color(float r, float g, float b);

#endif // SK_SHADER_API