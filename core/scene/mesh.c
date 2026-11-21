#include <scene/mesh.h>

mesh_t* mesh_create(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count) {
  mesh_t* mesh = {0};

  mesh->vertices = vertices;
  mesh->vec_count = vec_count;
  mesh->indices = indices;
  mesh->ind_count = ind_count;

  return mesh;
}
