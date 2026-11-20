#ifndef MESH_H
#define MESH_H 

#include <stdint.h>

#include <math/matrix.h>
#include <math/vector.h>

typedef struct {
  vec3f_t* vertices;
  int vec_count;

  uint16_t* indices;
  int ind_count;
} mesh_t;

void build_plane(mesh_t* mesh, float width, float height);

#endif 
