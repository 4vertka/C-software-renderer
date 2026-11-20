#include "matrix.h"

mat4x4_t mat4_create(float diagonal) {                                              
 return (mat4x4_t) {{                                                               
    {diagonal, 0, 0, 0},                                                            
    {0, diagonal, 0, 0},                                                            
    {0, 0, diagonal, 0},                                                            
    {0, 0, 0, diagonal}                                                             
  }};                                                                               
}                                                                                   
                                                                                    
mat4x4_t mat4_mul_mat4(mat4x4_t a, mat4x4_t b) {                                    
  mat4x4_t res;                                                                     
                                                                                    
  for (int i = 0; i < 4; i++) {                                                     
    for (int j = 0; j < 4; j++) {                                                   
      res.m[i][j] = 0;                                                              
                                                                                    
      for (int k = 0; k < 4; k++)                                                   
        res.m[i][j] += a.m[i][k] * b.m[k][j];                                       
    }                                                                               
  }                                                                                 
  return res;                                                                       
}                                                                                   
                                                                                    
vec4f_t mat4_mul_vec4(mat4x4_t m, vec4f_t v) {                                      
  vec4f_t res;              
  res.x = m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3]*v.w;
  res.y = m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3]*v.w;
  res.z = m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3]*v.w;
  res.w = m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3]*v.w;
  return res;                                                                       
}                                                                                   
                                                                                    
mat4x4_t mat4_scale(mat4x4_t m, vec3f_t v) {                                        
  mat4x4_t scale = {{                                                               
    {v.x, 0,    0,  0},                                                             
    {0,   v.y,  0,  0},                                                             
    {0,   0,    v.z,0},                                                             
    {0,   0,    0,  1}                                                              
  }};                                                                               
                                                                                    
  return mat4_mul_mat4(m, scale);                                                   
}                                                                                   
                                                                                    
mat4x4_t mat4_translation(mat4x4_t m, vec3f_t v) {                                  
  mat4x4_t trans = {{                                                               
    {1, 0, 0, v.x},                                                                 
    {0, 1, 0, v.y},                                                                 
    {0, 0, 1, v.z},                                                                 
    {0, 0, 0, 1}                                                                    
  }};                                                                               
                                                                                    
  return mat4_mul_mat4(m, trans);                                                   
}                                                                                   
                                                                                    
mat4x4_t mat4_rotate(mat4x4_t m, float angle, vec3f_t v) {                          
  float e = angle * (M_PI / 180);                                                   
                                                                                    
  float r1c1 = cos(e) + v.x*v.x * (1 - cos(e));                                     
  float r1c2 = v.x * v.y * (1 - cos(e)) - v.z * sin(e);                             
  float r1c3 = v.x * v.z * (1 - cos(e)) + v.y * sin(e);                             
                                                                                    
  float r2c1 = v.y * v.x * (1 - cos(e)) + v.z * sin(e);                             
  float r2c2 = cos(e) + v.y*v.y * (1 - cos(e));                                     
  float r2c3 = v.y * v.z * (1 - cos(e)) - v.x * sin(e);                             
                                                                                    
  float r3c1 = v.z * v.x * (1 - cos(e)) - v.y * sin(e);                             
  float r3c2 = v.z * v.y * (1 - cos(e)) + v.x * sin(e);                             
  float r3c3 = cos(e) + v.z*v.z * (1 - cos(e));                                     
                                                                                    
  mat4x4_t rotate = {{                                                              
    {r1c1, r1c2, r1c3, 0},                                                          
    {r2c1, r2c2, r2c3, 0},                                                          
    {r3c1, r3c2, r3c3, 0},                                                          
    {0,    0,    0,    1}                                                           
  }};                                                                               
                                                                                    
  return mat4_mul_mat4(m, rotate);                                                  
}                                                                                   
                                                                                    
mat4x4_t mat4_perspective(float fov, float a, float near, float far) {              
  float f = 1.0f / tanf(fov * (float)M_PI / 180.0f / 2.0f);                                                      
                                                                                    
  return (mat4x4_t) {{                                                              
    {f/a,   0, 0,                       0},                                         
    {0,     f, 0,                       0},                                         
    {0,     0, ((far+near)/(near-far)), ((2*far*near)/(near-far))},                 
    {0,     0, -1,                      0},                                         
  }};                                                                               
}

mat4x4_t mat4_lookat(vec3f_t eye, vec3f_t target, vec3f_t up){

  mat4x4_t res;
  return res;
}
                                                                                    
