cmake_minimum_required(VERSION 3.16)
project(sk_realtime_renderer)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

include_directories(src)

add_executable(sk_realtime_renderer
    src/main.c
    src/app/app.c
    src/app/app_events.c
    src/shader_api/shader_api.c
    src/shader_api/render_cmd_system.c
    src/shader_api/renderable_obj.c
    src/game/game.c
    src/game/triangle.c
)

find_package(OpenGL REQUIRED)

# Link to the actual SDL3 library and the system OpenGL library.
target_link_libraries(sk_realtime_renderer PRIVATE SDL3::SDL3 OpenGL::GL)
