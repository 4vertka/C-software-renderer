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

  mat4x4_t view_mat;
  mat4x4_t projection_mat;
} camera_t;

camera_t* camera_create(float fov,
                        float aspect,
                        float near,
                        float far,
                        vec3f_t pos,
                        vec3f_t target);

#endif 
