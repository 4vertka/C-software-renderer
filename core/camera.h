#ifndef CAMERA_H 
#define CAMERA_H

#include <math/vector.h>
#include <math/matrix.h>

typedef struct {
  vec3f_t position;
  vec3f_t target;
  vec3f_t rotation;

  float fov;
  float aspect;
  float near;
  float far;

  mat4x4_t view;
  mat4x4_t projection;

} camera_t;

#endif 
