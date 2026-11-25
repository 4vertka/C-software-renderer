#include <scene/mesh.h>

#include <stdlib.h>
#include <string.h>

/*
mesh_t* mesh_create(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count) {
  mesh_t* mesh = malloc(sizeof *mesh);
  if (!mesh) return NULL;

  mesh->vertices = malloc(vec_count*sizeof(*mesh->vertices));
  mesh->indices = malloc(ind_count*sizeof(*mesh->indices));
  if (!mesh->vertices || !mesh->indices) {
    mesh_free(mesh);
    return NULL;
  }

  memcpy(mesh->vertices, vertices, vec_count * sizeof(*vertices));
  memcpy(mesh->indices, indices, ind_count * sizeof(*indices));

  mesh->vec_count = vec_count;
  mesh->ind_count = ind_count;

  return mesh;
}
*/

mesh_t* mesh_create(vertex_t* vertices, int vec_count, face_t* indices, int face_count) {
  mesh_t* mesh = malloc(sizeof *mesh);
  if (!mesh) return NULL;

  mesh->vertices = malloc(vec_count*sizeof(*mesh->vertices));
  mesh->faces = malloc(face_count*sizeof(*mesh->faces));
  if (!mesh->vertices || !mesh->faces) {
    mesh_free(mesh);
    return NULL;
  }

  memcpy(mesh->vertices, vertices, vec_count * sizeof(*vertices));
  memcpy(mesh->faces, indices, face_count * sizeof(*indices));

  mesh->vec_count = vec_count;
  mesh->face_count = face_count;

  return mesh;
}

void mesh_free(mesh_t* mesh) {
  free(mesh->vertices);
  free(mesh->faces);
  free(mesh->line_faces);
  free(mesh);
}
