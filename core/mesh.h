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

#endif 
