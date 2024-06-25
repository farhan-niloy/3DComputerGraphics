#include "array.h"
#include "display.h"
#include "mesh.h"
#include "triangle.h"
#include "vector.h"
#include <_ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

triangle_t *triangles_to_render = NULL;

float fov_factor = 800.0f;
vec3_t camera_position = {.x = 0.0f, .y = 0.0f, .z = -120.0f};

int previous_frame_time = 0;

void setup() {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
  char *filename = "f22.obj";
  load_obj_file_data(filename);

  vec3_t a = {2.5, 6.4, 3.0};
  vec3_t b = {-2.2, 1.4, -1.0};

  // float array_length = vec3_length(a);
  // float brray_length = vec3_length(b);
}

void process_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        is_running = false;
      break;
    }
  }
}

vec2_t project(vec3_t point) {
  vec2_t projected_point = {.x = (fov_factor * point.x) / point.z,
                            .y = (fov_factor * point.y) / point.z};
  return projected_point;
}

void update() {

  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  previous_frame_time = SDL_GetTicks();

  // initialize the array of triangles to render
  triangles_to_render = NULL;

  mesh.rotation.y += 0.01f;
  mesh.rotation.z += 0.01f;
  mesh.rotation.x += 0.01f;

  // Loop all triangle faces
  int num_faces = array_length(mesh.faces);
  for (int i = 0; i < num_faces; i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    triangle_t projected_triangle;

    // Loop all three verticces of this current face and apply transformation
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

      // Translate the vertex away from the camera
      transformed_vertex.z -= camera_position.z;

      // Project current vertex
      vec2_t projected_point = project(transformed_vertex);

      // Scale and translate the projected point to the middle of the screen
      projected_point.x += (float)(window_width) / 2.0f;
      projected_point.y += (float)(window_height) / 2.0f;

      projected_triangle.points[j] = projected_point;
    }

    // Save the projected triangle in the array of triangles to render
    array_push(triangles_to_render, projected_triangle);
  }
}

void render() {

  // Loop all projected triangles and render them
  int num_triangles = array_length(triangles_to_render);
  for (int i = 0; i < num_triangles; i++) {
    triangle_t triangle = triangles_to_render[i];
    draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
    draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
    draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

    draw_triangle(triangle.points[0].x, triangle.points[0].y,
                  triangle.points[1].x, triangle.points[1].y,
                  triangle.points[2].x, triangle.points[2].y, 0xFF00FF00);
  }

  // Clear the array of triangles to render every frame Loop
  array_free(triangles_to_render);

  draw_grid(0xFFFFFF00);

  render_color_buffer();

  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

void free_resources(void) {
  free(color_buffer);
  array_free(mesh.faces);
  array_free(mesh.vertices);
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  free_resources();

  return 0;
}
