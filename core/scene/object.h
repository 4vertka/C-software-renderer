#ifndef OBJECT_H 
#define OBJECT_H

#include <scene/mesh.h>
#include <scene/transform.h>

typedef struct {
  mesh_t* mesh;
  transform_t transform;
  uint32_t color;
} object_t;

object_t* object_create(const mesh_t* mesh, transform_t transform, uint32_t color);

#endif 
