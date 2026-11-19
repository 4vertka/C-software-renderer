#include "renderer.h"

mat4x4_t build_model_mat(float angle, vec3f_t axis) {                                                 
  mat4x4_t model = mat4_create(1.0f);                                                                 
  model = mat4_rotate(model, angle, axis);                                                            
                                                                                                      
  return model;                                                                                       
}                                                                                                     
                                                                                                      
mat4x4_t build_view_mat(vec3f_t pos) {                                                                
  mat4x4_t view = mat4_create(1.0f);                                                                  
  view = mat4_translation(view, pos);                                                                 
                                                                                                      
  return view;                                                                                        
}                                                                                                     
                                                                                                      
mat4x4_t build_projection_mat(float fov, float aspect, float near, float far) {                       
  mat4x4_t proj = mat4_perspective(fov, aspect, near, far);                                           
                                                                                                      
  return proj;                                                                                        
}                                                                                                     
                                                                                                      
mat4x4_t build_mvp_mat(mat4x4_t proj, mat4x4_t view, mat4x4_t model) {                                
  mat4x4_t mvp = mat4_mul_mat4(mat4_mul_mat4(proj, view), model);                                     
                                                                                                      
  return mvp;                                                                                         
}                                                                                                     
                                                                                                      
vec4f_t build_mvp_position(mat4x4_t mvp, vec3f_t pos) {                                                   
  vec4f_t position = mat4_mul_vec4(mvp, (vec4f_t){pos.x, pos.y, pos.z, 1.0f});                        
                                                                                                      
  return position;                                                                                    
}          

vec4f_t build_color(vec3f_t color) {
  return (vec4f_t) {color.x, color.y, color.z, 1.0f};
}
