#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math/vector.h>
#include <math/matrix.h>

typedef struct {
  vec3f_t position;
  vec3f_t rotation;
  vec3f_t scale;
} transform_t;

transform_t* transform_create(vec3f_t position, vec3f_t rotation, vec3f_t scale);
mat4x4_t transform_to_mat(const transform_t* t);

#endif 

