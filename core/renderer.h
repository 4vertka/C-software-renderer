#ifndef RENDERER_H
#define RENDERER_H 

#include <stdint.h>

#include "math/vector.h"
#include "math/matrix.h"

typedef struct {           
  uint32_t* buffer;        
  int width;               
  int height;              
} framebuffer_t;          

mat4x4_t build_model_mat(float angle, vec3f_t axis);
mat4x4_t build_view_mat(vec3f_t pos);
mat4x4_t build_projection_mat(float fov, float aspect, float near, float far);
mat4x4_t build_mvp_mat(mat4x4_t proj, mat4x4_t view, mat4x4_t model);

vec4f_t build_mvp_position(mat4x4_t mvp, vec3f_t pos);
vec4f_t build_color(vec3f_t color);

#endif 
