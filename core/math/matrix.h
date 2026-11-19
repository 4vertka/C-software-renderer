#ifndef MATRIX_H
#define MATRIX_H 

#include "vector.h"
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846

typedef struct {
  float m[4][4];
} mat4x4_t;

mat4x4_t mat4_create(float diagonal);

mat4x4_t mat4_mul_mat4(mat4x4_t a, mat4x4_t b);
vec4f_t mat4_mul_vec4(mat4x4_t m, vec4f_t v);

mat4x4_t mat4_scale(mat4x4_t m, vec3f_t v);
mat4x4_t mat4_translation(mat4x4_t m, vec3f_t v);
mat4x4_t mat4_rotate(mat4x4_t m, float angle, vec3f_t v);
mat4x4_t mat4_perspective(float fov, float a, float near, float far);
mat4x4_t mat4_lookat(vec3f_t eye, vec3f_t target, vec3f_t up);
#endif 
