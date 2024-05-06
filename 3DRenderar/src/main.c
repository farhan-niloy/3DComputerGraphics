#include "display.h"
#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>

#define N_POINTS (9 * 9 * 9)

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 640.0f;
vec3_t camera_position = {.x = 0.0f, .y = 0.0f, .z = -5.0f};
vec3_t cube_rotation = {.x = 0.0f, .y = 0.0f, .z = 0.0f};

int previous_frame_time = 0;

void setup() {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);

  int point_count = 0;

  for (float x = -1.0f; x <= 1.0f; x += 0.25f) {
    for (float y = -1.0f; y <= 1.0f; y += 0.25f) {
      for (float z = -1.0f; z <= 1.0f; z += 0.25f) {
        vec3_t new_point = {.x = x, .y = y, .z = z};
        cube_points[point_count++] = new_point;
      }
    }
  }
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

  while (!SDL_TICKS_PASSED(SDL_GetTicks(),
                           previous_frame_time + FRAME_TARGET_TIME))
    ;

  previous_frame_time = SDL_GetTicks();

  cube_rotation.x += 0.01f;
  cube_rotation.z += 0.01f;
  cube_rotation.x += 0.01f;

  for (int i = 0; i < N_POINTS; i++) {
    vec3_t point = cube_points[i];

    vec3_t transformed_point = vec3_rotate_x(point, cube_rotation.x);
    transformed_point = vec3_rotate_y(transformed_point, cube_rotation.y);
    transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);

    transformed_point.z -= camera_position.z;

    vec2_t projected_point = project(transformed_point);

    projected_points[i] = projected_point;
  }
}

void render() {
  for (int i = 0; i < N_POINTS; i++) {
    vec2_t projected_point = projected_points[i];
    draw_rect(projected_point.x + ((float)window_width / 2),
              projected_point.y + ((float)window_height / 2), 4, 4, 0xFFFFFF00);
  }

  render_color_buffer();

  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
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

  free(color_buffer);

  return 0;
}
