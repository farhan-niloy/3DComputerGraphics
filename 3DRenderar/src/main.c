#include </opt/homebrew/Cellar/sdl2/2.30.2/include/SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  // Create a SDL window
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_BORDERLESS);

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

int main(void) {

  /* TODO: Create a SDL window */

  is_running = initialize_window();

  return 0;
}
