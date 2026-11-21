#include "vector.h"

//vec2 
float vec2_dot(vec2f_t a, vec2f_t b) {                                                     
  return a.x*b.x + a.y*b.y;                                                                
}                                                                                          
       
//vec3 
float vec3_dot(vec3f_t a, vec3f_t b) {                                                     
  return a.x*b.x + a.y*b.y + a.z*b.z;                                                      
}                                                                                          

vec3f_t vec3_cross(vec3f_t a, vec3f_t b) {                                              
  return (vec3f_t) {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};           
}    

float vec3_length_squared(vec3f_t a) {
  return a.x*a.x + a.y*a.y + a.z*a.z;
}

float vec3_length(vec3f_t a) {
  return sqrt(vec3_length_squared(a));
} 

vec3f_t vec3_unit(vec3f_t a) {
  return vec3_div_scalar(a, vec3_length(a)); 
}                              

vec3f_t vec3_div_scalar(vec3f_t a, float scalar) {
  return (vec3f_t) {a.x/scalar, a.y/scalar, a.z/scalar};
}

vec3f_t vec3_minus_vec3(vec3f_t a, vec3f_t b) {
  return (vec3f_t) {a.x - b.x, a.y - b.y, a.z - b.z};
}

//vec4
float vec4_dot(vec4f_t a, vec4f_t b) {                                                     
  return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;                                            
}                                                                                          
                                                                                           
   
   
   
