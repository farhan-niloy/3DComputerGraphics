#include "display.h"
#include <stdbool.h>

void setup() {

  // Allocate the required memory in the bytes to hold the coor buffer
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  // Creating a SDL texture that is used to display the color buffer
  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
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

void update() {}

void render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_color_buffer();

  cleear_color_buffer(0xFF000000);

  // grid_color(0xFF808080);

  draw_rect(400, 250, 300, 150, 0xFFFF0000);
  draw_pent(window_width / 2, window_height / 2, 200, 0xFFFFFFFF);

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

  return 0;
}
