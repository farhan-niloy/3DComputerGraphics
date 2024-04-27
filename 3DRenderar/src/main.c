#include </opt/homebrew/Cellar/sdl2/2.30.2/include/SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int window_width = 800;
int window_height = 600;

uint32_t *color_buffer = NULL;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

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

  return true;
}

void setup() {

  // TODO:
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
}

void process_input() {
  // TODO:

  SDL_Event event;
  SDL_PollEvent(&event);

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

void update() {
  // TODO:
}

void render() {
  // TODO:
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_Quit();
}

void destroy_window() {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

int main(void) {

  /* TODO: Create a SDL window */

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
