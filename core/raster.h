#ifndef RASTER_H
#define RASTER_H 

#include <math/vector.h>
#include <framebuffer.h>

typedef struct {
  float u;
  float v;
} tex2_t;

typedef struct {
  vec3f_t position;
  vec3f_t normal;
  tex2_t uv;
  uint32_t color;
} vertex_t;

typedef struct {
  int a;
  int b;
  int c;
  tex2_t a_uv;
  tex2_t b_uv;
  tex2_t c_uv;
  uint32_t color;
} face_t;

void plot_line(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);                             
void plot_line_high(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);                        
void plot_line_low(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);          

void plot_triangle_wireframe(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, uint32_t color);
void plot_triangle(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, uint32_t color);             

#endif 
