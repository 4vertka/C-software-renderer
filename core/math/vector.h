#ifndef VECTOR_H 
#define VECTOR_H

#include <math.h>

typedef struct {
  float x;
  float y;
} vec2f_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3f_t;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} vec4f_t;

//vec2 
float vec2_dot(vec2f_t a, vec2f_t b);

//vec3 
float vec3_dot(vec3f_t a, vec3f_t b);
vec3f_t vec3_cross(vec3f_t a, vec3f_t b);
float vec3_length_squared(vec3f_t a);
float vec3_length(vec3f_t a);
vec3f_t vec3_unit(vec3f_t a);
vec3f_t vec3_div_scalar(vec3f_t a, float scalar);

vec3f_t vec3_minus_vec3(vec3f_t a, vec3f_t b);

//vec4
float vec4_dot(vec4f_t a, vec4f_t b);

#endif 
