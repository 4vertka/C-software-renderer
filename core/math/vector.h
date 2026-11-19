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

float vec2_dot(vec2f_t a, vec2f_t b) {
  return a.x*b.x + a.y*b.y;
}

float vec3_dot(vec3f_t a, vec3f_t b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

float vec4_dot(vec4f_t a, vec4f_t b) {
  return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

vec3f_t vec2_cross(vec3f_t a, vec3f_t b) {
  return (vec3f_t) {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}


#endif 
