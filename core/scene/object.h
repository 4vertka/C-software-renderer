#ifndef OBJECT_H 
#define OBJECT_H

#include <scene/mesh.h>
#include <scene/transform.h>

typedef enum {          
  RENDER_FILLED,        
  RENDER_WIREFRAME      
} render_mode_e;        

typedef struct {
  const mesh_t* mesh;
  transform_t transform;
  uint32_t color;
  render_mode_e mode;
} object_t;

object_t* object_create(const mesh_t* mesh, transform_t transform, uint32_t color, render_mode_e mode);

void object_free(object_t* obj);

#endif 
