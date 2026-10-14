#include "shader_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sk_shader_t shaders[10];

sk_shader_id_t sk_create_shader(const char* vert_file_path, const char* frag_file_path) { 

    static unsigned int running_id = 0; 

    sk_shader_t* shader = &shaders[running_id];
    shader->id = running_id;
    running_id++;

    const char* vert_shader_src = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    char frag_shader_src[1024];
    memset(frag_shader_src, 0, sizeof(frag_shader_src));
    const char* frag_shader_src_template = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(%ff, %ff, %ff, 1.0f);\n"
        "}\n\0";

    sprintf(frag_shader_src, frag_shader_src_template,
        (float)rand() / (float)RAND_MAX,
        (float)rand() / (float)RAND_MAX,
        (float)rand() / (float)RAND_MAX);

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_src, NULL);
    glCompileShader(vert_shader);

    int success;
    char infoLog[512];
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
        // std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    char* frag_shader_ptr = frag_shader_src;
    glShaderSource(frag_shader, 1, &frag_shader_ptr, NULL);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
        // std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shader->shader_program = glCreateProgram();
    glAttachShader(shader->shader_program, vert_shader);
    glAttachShader(shader->shader_program, frag_shader);
    glLinkProgram(shader->shader_program);

    glGetProgramiv(shader->shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->shader_program, 512, NULL, infoLog);
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return shader->id;
}

void sk_bind_shader(sk_shader_id_t id) {
    glUseProgram(shaders[id].shader_program);
}

void sk_shader_set_viewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void sk_shader_clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sk_shader_set_clear_color(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}
