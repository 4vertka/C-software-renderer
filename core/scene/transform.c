#include "transform.h"

transform_t transform_create(vec3f_t position, vec3f_t rotation, vec3f_t scale) {
  transform_t transform = {0};

  transform.position = position;
  transform.rotation = rotation;
  transform.scale = scale;

  return transform;
}

mat4x4_t transform_to_mat(const transform_t* t) {
  mat4x4_t trans = mat4_create(1.0f);

  trans = mat4_translation(trans, t->position);
  trans = mat4_rotate(trans, t->rotation.x, (vec3f_t){1,0,0});
  trans = mat4_rotate(trans, t->rotation.y, (vec3f_t){0,1,0});
  trans = mat4_rotate(trans, t->rotation.z, (vec3f_t){0,0,1});
  trans = mat4_scale(trans, t->scale);

  return trans;
}
