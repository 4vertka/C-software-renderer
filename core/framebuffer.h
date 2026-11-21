#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct {                 
  uint32_t* buffer;              
  int width;                     
  int height;                    
} framebuffer_t;                 

void set_pixel(framebuffer_t* fb, int x, int y, uint32_t color);          

#endif 
