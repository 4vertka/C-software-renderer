#include <scene/object.h>

#include <stdlib.h>

object_t* object_create(const mesh_t* mesh, transform_t transform, uint32_t color, render_mode_e mode) {
  object_t* obj = malloc(sizeof(*obj));
  if (!obj) return NULL;

  obj->mesh = mesh;
  obj->transform = transform;
  obj->color = color;
  obj->mode = mode;

  return obj;
}

void object_free(object_t* obj) {
  free(obj);
}
