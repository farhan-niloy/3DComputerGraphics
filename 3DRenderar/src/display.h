#ifndef DISPLAY_H
#define DISPLAY_H

#include </opt/homebrew/Cellar/sdl2/2.30.2/include/SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

extern bool is_running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int window_width;
extern int window_height;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

bool initialize_window(void);
void render_color_buffer();
void cleear_color_buffer(uint32_t color);
void draw_pix(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_grid(uint32_t color);
void draw_pent(int x, int y, int line, uint32_t color);
void destroy_window();

#endif
