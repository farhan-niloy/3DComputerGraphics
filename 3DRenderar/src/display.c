#include "display.h"
#include <time.h>

bool is_running = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int window_width = 800;
int window_height = 600;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  // Use SDL to query what is the fullscreen max. width and height
  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  window_width = display_mode.w;
  window_height = display_mode.h;

  // Create a SDL window
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window_width, window_height, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error Creating SDL window!");
    return false;
  }

  // Create a SDL renderer
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    return true;
    fprintf(stderr, "Error creating SDL renderer.\n");
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (window_width * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void cleear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; y++) {
    for (int x = 0; x < window_width; x++) {
      color_buffer[(window_width * y) + (x + 10)] = color;
    }
  }
}

void draw_pix(int x, int y, uint32_t color) {
  color_buffer[(window_width * y) + x] = color;
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      int current_x = x + i;
      int current_y = y + j;
      color_buffer[(window_width * current_y) + current_x] = color;
    }
  }
}

void draw_pent(int x, int y, int line, uint32_t color) {
  for (int i = 0; i < line; i++) {
    for (int j = 0; j < line; j++) {
      int pos_x = x + i;
      int d = y + j;
      color_buffer[(window_width * pos_x) + d] = color;
    }
    y++;
    line--;
  }
}

void grid_color(uint32_t color) {
  for (int y = 0; y < window_height; y += 40) {
    for (int x = 0; x < window_width; x += 40) {
      color_buffer[window_width * y + x] = color;
    }
  }
}

void destroy_window() {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}
