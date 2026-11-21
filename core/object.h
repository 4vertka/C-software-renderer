#ifndef OBJECT_H 
#define OBJECT_H

#include <mesh.h>
#include <transform.h>

typedef struct {
  const mesh_t* mesh;
  transform_t transform;
  uint32_t color;
} object_t;

#endif 
