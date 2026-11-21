#include <raster.h>

#include <math.h>
#include <utils.h>
#include <stdlib.h>

void plot_line(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color)                                                                                                      
{                                                                                                                                                                              
  if (abs((int)P1.y - (int)P0.y) < abs((int)P1.x - (int)P0.x))                                                                                                                 
  {                                                                                                                                                                            
    if (P0.x > P1.x)                                                                                                                                                           
      plot_line_low(fb, P1, P0, color);                                                                                                                                        
    else                                                                                                                                                                       
      plot_line_low(fb, P0, P1, color);                                                                                                                                        
  }                                                                                                                                                                            
  else                                                                                                                                                                         
  {                                                                                                                                                                            
    if (P0.y > P1.y)                                                                                                                                                           
      plot_line_high(fb, P1, P0, color);                                                                                                                                       
    else                                                                                                                                                                       
      plot_line_high(fb, P0, P1, color);                                                                                                                                       
  }                                                                                                                                                                            
}                                                                                                                                                                              
                                                                                                                                                                               
void plot_line_high(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color)                                                                                                 
{                                                                                                                                                                              
  int dx = P1.x - P0.x;                                                                                                                                                        
  int dy = P1.y - P0.y;                                                                                                                                                        
  int xi = 1;                                                                                                                                                                  
                                                                                                                                                                               
  if (dx < 0)                                                                                                                                                                  
  {                                                                                                                                                                            
    xi = -1;                                                                                                                                                                   
    dx = -dx;                                                                                                                                                                  
  }                                                                                                                                                                            
                                                                                                                                                                               
  int D = (2 * dx) - dy;                                                                                                                                                       
  int x = P0.x;                                                                                                                                                                
                                                                                                                                                                               
  for (int y = P0.y; y <= P1.y; y++)                                                                                                                                           
  {                                                                                                                                                                            
    set_pixel(fb, x, y, color);                                                                                                                                                
    if (D > 0)                                                                                                                                                                 
    {                                                                                                                                                                          
      x = x + xi;                                                                                                                                                              
      D = D + (2 * (dx - dy));                                                                                                                                                 
    }                                                                                                                                                                          
    else                                                                                                                                                                       
    {                                                                                                                                                                          
      D = D + 2*dx;                                                                                                                                                            
    }                                                                                                                                                                          
  }                                                                                                                                                                            
}                                                                                                                                                                              
                                                                                                                                                                               
void plot_line_low(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, uint32_t color)                                                                                                  
{                                                                                                                                                                              
  int dx = P1.x - P0.x;                                                                                                                                                        
  int dy = P1.y - P0.y;                                                                                                                                                        
  int yi = 1;                                                                                                                                                                  
                                                                                                                                                                               
  if (dy < 0)                                                                                                                                                                  
  {                                                                                                                                                                            
    yi = -1;                                                                                                                                                                   
    dy = -dy;                                                                                                                                                                  
  }                                                                                                                                                                            
                                                                                                                                                                               
  int D = (2 * dy) - dx;                                                                                                                                                       
  int y = P0.y;                                                                                                                                                                
                                                                                                                                                                               
  for (int x = P0.x; x <= P1.x; x++)                                                                                                                                           
  {                                                                                                                                                                            
    set_pixel(fb, x, y, color);                                                                                                                                                
    if (D > 0)                                                                                                                                                                 
    {                                                                                                                                                                          
      y = y + yi;                                                                                                                                                              
      D = D + (2 * (dy - dx));                                                                                                                                                 
    }                                                                                                                                                                          
    else                                                                                                                                                                       
    {                                                                                                                                                                          
      D = D + 2*dy;                                                                                                                                                            
    }                                                                                                                                                                          
  }                                                                                                                                                                            
}                                                                                                                                                                              
 
void plot_triangle_wireframe(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, uint32_t color) {
  plot_line(fb, P0, P1, color);
  plot_line(fb, P1, P2, color);
  plot_line(fb, P2, P0, color);
}

void plot_triangle(framebuffer_t* fb, vec3f_t P0, vec3f_t P1, vec3f_t P2, uint32_t color) {                                                                                    
                                                                                                                                                                               
  float area = (P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y);                                                                                                  
  if (area > 0) {                                                                                                                                                              
    vec3f_t tmp = P1;                                                                                                                                                          
    P1 = P2;                                                                                                                                                                   
    P2 = tmp;                                                                                                                                                                  
  }                                                                                                                                                                            
                                                                                                                                                                               
  //fixed point coordinates                                                                                                                                                    
  const int Y1 = roundf(16.0f * P0.y);                                                                                                                                         
  const int Y2 = roundf(16.0f * P1.y);                                                                                                                                         
  const int Y3 = roundf(16.0f * P2.y);                                                                                                                                         
                                                                                                                                                                               
  const int X1 = roundf(16.0f * P0.x);                                                                                                                                         
  const int X2 = roundf(16.0f * P1.x);                                                                                                                                         
  const int X3 = roundf(16.0f * P2.x);                                                                                                                                         
                                                                                                                                                                               
  //const delta val                                                                                                                                                            
  const int DX12 = X1 - X2;                                                                                                                                                    
  const int DX23 = X2 - X3;                                                                                                                                                    
  const int DX31 = X3 - X1;                                                                                                                                                    
                                                                                                                                                                               
  const int DY12 = Y1 - Y2;                                                                                                                                                    
  const int DY23 = Y2 - Y3;                                                                                                                                                    
  const int DY31 = Y3 - Y1;                                                                                                                                                    
                                                                                                                                                                               
  //fixed point deltas                                                                                                                                                         
  const int FDX12 = DX12 << 4;                                                                                                                                                 
  const int FDX23 = DX23 << 4;                                                                                                                                                 
  const int FDX31 = DX31 << 4;                                                                                                                                                 
                                                                                                                                                                               
  const int FDY12 = DY12 << 4;                                                                                                                                                 
  const int FDY23 = DY23 << 4;                                                                                                                                                 
  const int FDY31 = DY31 << 4;                                                                                                                                                 
                                                                                                                                                                               
  int minx = (MIN3(X1, X2, X3) + 0xF)>>4;                                                                                                                                      
  int maxx = (MAX3(X1, X2, X3) + 0xF)>>4;                                                                                                                                      
  int miny = (MIN3(Y1, Y2, Y3) + 0xF)>>4;                                                                                                                                      
  int maxy = (MAX3(Y1, Y2, Y3) + 0xF)>>4;                                                                                                                                      
                                                                                                                                                                               
  if (minx < 0) minx = 0;                                                                                                                                                      
  if (miny < 0) miny = 0;                                                                                                                                                      
  if (maxx > fb->width) maxx = fb->width;                                                                                                                                      
  if (maxy > fb->height) maxy = fb->height;                                                                                                                                    
                                                                                                                                                                               
  // block size                                                                                                                                                                
  const int q = 8;                                                                                                                                                             
                                                                                                                                                                               
  minx &= ~(q - 1);                                                                                                                                                            
  miny &= ~(q - 1);                                                                                                                                                            
                                                                                                                                                                               
  //half edge detection                                                                                                                                                        
  int C1 = DY12 * X1 - DX12 * Y1;                                                                                                                                              
  int C2 = DY23 * X2 - DX23 * Y2;                                                                                                                                              
  int C3 = DY31 * X3 - DX31 * Y3;                                                                                                                                              
                                                                                                                                                                               
  if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;                                                                                                                                
  if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;                                                                                                                                
  if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;                                                                                                                                
                                                                                                                                                                               
  for (int y = miny; y < maxy; y+=q) {                                                                                                                                         
    for (int x = minx; x < maxx; x+=q) {                                                                                                                                       
      int x0 = x << 4;                                                                                                                                                         
      int x1 = (x + q - 1) << 4;                                                                                                                                               
      int y0 = y << 4;                                                                                                                                                         
      int y1 = (y + q - 1) << 4;                                                                                                                                               
                                                                                                                                                                               
      // Evaluate half-space functions                                                                                                                                         
      uint8_t a00 = C1 + DX12 * y0 - DY12 * x0 > 0;                                                                                                                            
      uint8_t a10 = C1 + DX12 * y0 - DY12 * x1 > 0;                                                                                                                            
      uint8_t a01 = C1 + DX12 * y1 - DY12 * x0 > 0;                                                                                                                            
      uint8_t a11 = C1 + DX12 * y1 - DY12 * x1 > 0;                                                                                                                            
      int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);                                                                                                               
                                                                                                                                                                               
      uint8_t b00 = C2 + DX23 * y0 - DY23 * x0 > 0;                                                                                                                            
      uint8_t b10 = C2 + DX23 * y0 - DY23 * x1 > 0;                                                                                                                            
      uint8_t b01 = C2 + DX23 * y1 - DY23 * x0 > 0;                                                                                                                            
      uint8_t b11 = C2 + DX23 * y1 - DY23 * x1 > 0;                                                                                                                            
      int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);                                                                                                               
                                                                                                                                                                               
      uint8_t c00 = C3 + DX31 * y0 - DY31 * x0 > 0;                                                                                                                            
      uint8_t c10 = C3 + DX31 * y0 - DY31 * x1 > 0;                                                                                                                            
      uint8_t c01 = C3 + DX31 * y1 - DY31 * x0 > 0;                                                                                                                            
      uint8_t c11 = C3 + DX31 * y1 - DY31 * x1 > 0;                                                                                                                            
      int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);                                                                                                               
                                                                                                                                                                               
      // Skip block when outside an edge                                                                                                                                       
      if(a == 0x0 || b == 0x0 || c == 0x0) continue;                                                                                                                           
                                                                                                                                                                               
      if(a == 0xF && b == 0xF && c == 0xF) {                                                                                                                                   
        for(int iy = y; iy < y+q; iy++) {                                                                                                                                      
          for(int ix = x; ix < x+q; ix++)                                                                                                                                      
            if (ix < fb->width && iy < fb->height)                                                                                                                             
              set_pixel(fb, ix, iy, color);                                                                                                                                    
        }                                                                                                                                                                      
      }                                                                                                                                                                        
      else {                                                                                                                                                                   
        int CY1 = C1 + DX12 * y0 - DY12 * x0;                                                                                                                                  
        int CY2 = C2 + DX23 * y0 - DY23 * x0;                                                                                                                                  
        int CY3 = C3 + DX31 * y0 - DY31 * x0;                                                                                                                                  
                                                                                                                                                                               
        for(int iy = y; iy < y + q; iy++) {                                                                                                                                    
          int CX1 = CY1;                                                                                                                                                       
          int CX2 = CY2;                                                                                                                                                       
          int CX3 = CY3;                                                                                                                                                       
                                                                                                                                                                               
          for(int ix = x; ix < x + q; ix++) {                                                                                                                                  
            if(CX1 > 0 && CX2 > 0 && CX3 > 0)                                                                                                                                  
              if (ix < fb->width && iy < fb->height)                                                                                                                           
                set_pixel(fb, ix, iy, color);                                                                                                                                  
            CX1 -= FDY12;                                                                                                                                                      
            CX2 -= FDY23;                                                                                                                                                      
            CX3 -= FDY31;                                                                                                                                                      
          }                                                                                                                                                                    
          CY1 += FDX12;                                                                                                                                                        
          CY2 += FDX23;                                                                                                                                                        
          CY3 += FDX31;                                                                                                                                                        
        }                                                                                                                                                                      
      }                                                                                                                                                                        
    }                                                                                                                                                                          
                                                                                                                                                                               
  }                                                                                                                                                                            
}                                                                                                                                                                              
