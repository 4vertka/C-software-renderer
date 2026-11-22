#ifndef CAMERA_H 
#define CAMERA_H

#include <math/vector.h>
#include <math/matrix.h>
#include "system/system.h"

typedef struct {
  vec3f_t position;
  vec3f_t rotation;
  
  vec3f_t eye;
  vec3f_t target;
  vec3f_t up;

  vec3f_t direction;
  vec3f_t right;

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
                        vec3f_t eye,
                        vec3f_t target,
                        vec3f_t up);

void camera_update(camera_t* camera, input_t* in, float dt);

void camera_free(camera_t* camera);

#endif 
