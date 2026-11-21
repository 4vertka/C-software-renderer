#include <scene/object.h>

object_t* object_create(const mesh_t* mesh, transform_t transform, uint32_t color) {
  object_t* obj = {0};
 
  obj->mesh = mesh;
  obj->transform = transform;
  obj->color = color;

  return obj;
}
