#include <scene/object.h>

#include <stdlib.h>

object_t* object_create(const mesh_t* mesh, transform_t transform, uint32_t color) {
  object_t* obj = malloc(sizeof(*obj));
  if (!obj) return NULL;

  obj->mesh = malloc(sizeof(*obj->mesh));
  if (!obj) {
    free(obj);
    return NULL;
  }

  memcpy(obj->mesh, mesh, sizeof(*mesh));

  obj->transform = transform;
  obj->color = color;

  return obj;
}
