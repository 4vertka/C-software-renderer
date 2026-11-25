#ifndef MESH_H 
#define MESH_H 

#include <stdint.h>
#include <math/vector.h>
#include <raster.h>

/*
typedef struct {                    
  vec3f_t* vertices;                
  uint16_t* indices;
  uint16_t* line_indices;
  int vec_count;                    
  int ind_count;         
  int li_count;
} mesh_t;                           
*/ 

typedef struct {
  vertex_t* vertices;
  face_t* faces;
  face_t* line_faces;
  int vec_count;
  int face_count;
  int liface_count;
} mesh_t;

//mesh_t* mesh_create(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count);
mesh_t* mesh_create(vertex_t* vertices, int vec_count, face_t* indices, int face_count);
void mesh_free(mesh_t* mesh);

#endif 
