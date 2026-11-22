#ifndef CAMERA_H 
#define CAMERA_H

#include <math/vector.h>
#include <math/matrix.h>
#include "system/system.h"

typedef struct {
  vec3f_t position;
  vec3f_t target;
  vec3f_t rotation;

  float fov;
  float aspect;
  float z_near;
  float z_far;
  float yaw;
  float pitch;
  
  mat4x4_t view_mat;
  mat4x4_t projection_mat;
} camera_t;

//void camera_update(camera_t* camera, input_t* in, float dt);

camera_t* camera_create(float fov, float aspect, float z_near, float z_far, vec3f_t position, vec3f_t target);

void camera_free(camera_t* camera);

#endif 
