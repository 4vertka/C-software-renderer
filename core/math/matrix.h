#ifndef MATRIX_H
#define MATRIX_H 

#include "vector.h"
#include <math.h>

#define M_PI 3.14159265358979323846

typedef struct {
  float m[4][4];
} mat4x4t_t;

mat4x4t_t mat4_create(float diagonal) {
  return (mat4x4t_t) {{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};
}

mat4x4t_t mat4_mul_mat4(mat4x4t_t a, mat4x4t_t b) {
  mat4x4t_t res;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      res.m[i][j] = 0;

      for (int k = 0; k < 4; k++)
        res.m[i][j] += a.m[i][k] * b.m[k][j];
    }
  }
  return res;
}

mat4x4t_t mat4_scale(mat4x4t_t m, vec3f_t v) {
  mat4x4t_t scale = {{
    {v.x, 0,    0,  0},
    {0,   v.y,  0,  0},
    {0,   0,    v.z,0},
    {0,   0,    0,  1}
  }};

  return mat4_mul_mat4(m, scale);
}

mat4x4t_t mat4_translation(mat4x4t_t m, vec3f_t v) {
  mat4x4t_t trans = {{
    {1, 0, 0, v.x},
    {0, 1, 0, v.y},
    {0, 0, 1, v.z},
    {0, 0, 0, 1}
  }};

  return mat4_mul_mat4(m, trans);
}

mat4x4t_t mat4_rotate(mat4x4t_t m, float angle, vec3f_t v) {
  float e = angle * (M_PI / 180);

  float r1c1 = cos(e) + v.x*v.x * (1 - cos(e));
  float r1c2 = v.x * v.y * (1 - cos(e)) - v.z * sin(e);
  float r1c3 = v.x * v.z * (1 - cos(e)) + v.y * sin(e);

  float r2c1 = v.y * v.x * (1 - cos(e)) + v.z * sin(e);
  float r2c2 = cos(e) + v.y*v.y * (1 - cos(e));
  float r2c3 = v.y * v.z * (1 - cos(e)) - v.x * sin(e);

  float r3c1 = v.z * v.x * (1 - cos(e)) - v.y * sin(e);
  float r3c2 = v.z * v.y * (1 - cos(e)) + v.x * sin(e);
  float r3c3 = cos(e) + v.z*v.z * (1 - cos(e));

  mat4x4t_t rotate = {{
    {r1c1, r1c2, r1c3, 0},
    {r2c1, r2c2, r2c3, 0},
    {r3c1, r3c2, r3c3, 0},
    {0,    0,    0,    1}
  }};

  return mat4_mul_mat4(m, rotate);
}

#endif 
