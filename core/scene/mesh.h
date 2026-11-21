#ifndef MESH_H 
#define MESH_H 

#include <stdint.h>
#include <math/vector.h>

typedef struct {                    
  vec3f_t* vertices;                
  uint16_t* indices;                
  int vec_count;                    
  int ind_count;                    
} mesh_t;                           

mesh_t* mesh_create(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count);
void mesh_free(mesh_t* mesh);

#endif 
