#ifndef RENDERER_H
#define RENDERER_H 

#include "math/vector.h"
#include "math/matrix.h"

mat4x4t_t build_model_mat(float angle, vec3f_t axis) {
  mat4x4t_t model = mat4_create(1.0f);
  model = mat4_rotate(model, angle, axis);

  return model;
}

mat4x4t_t build_view_mat(vec3f_t pos) {
  mat4x4t_t view = mat4_create(1.0f);
  view = mat4_translation(view, pos);

  return view;
}

mat4x4t_t build_projection_mat(float fov, float aspect, float near, float far) {
  mat4x4t_t proj = mat4_perspective(fov, aspect, near, far);

  return proj;
}

#endif 
