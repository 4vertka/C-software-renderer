#ifndef LINES_H 
#define LINES_H 

#include <stdint.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <math/vector.h>

#define MIN(a,b)      (((a)<(b))?(a):(b))
#define MAX(a,b)      (((a)>(b))?(a):(b))

#define MIN3(a,b,c)   (MIN(MIN(a,b), c))
#define MAX3(a,b,c)   (MAX(MAX(a,b), c))

typedef struct {
  float r;
  float g;
  float b;
  float a;
} color_t;

typedef struct {
  uint32_t* buffer;
  int width;
  int height;
} framebuffer_t;

void set_pixel(framebuffer_t* fb, float x, float y, color_t color);          
void plot_line(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, color_t color); 
void plot_line_high(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, color_t color);
void plot_line_low(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, color_t color);
void plot_triangle(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, color_t color);

#endif 
