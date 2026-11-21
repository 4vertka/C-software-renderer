#ifndef RASTER_H
#define RASTER_H 

#include <math/vector.h>
#include <framebuffer.h>

void plot_line(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);                             
void plot_line_high(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);                        
void plot_line_low(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color);                         
void plot_triangle(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, uint32_t color);             

#endif 
