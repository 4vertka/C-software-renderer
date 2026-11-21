#include "framebuffer.h"

void set_pixel(framebuffer_t* fb, int x, int y, uint32_t color)                                            
{                                                                                                          
  if (x < 0 || x >= fb->width || y < 0 || y >= fb->height) return;                                         
  fb->buffer[y * fb->width + x] = color;                                                                   
}                                                                                                          
