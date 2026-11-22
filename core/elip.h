#ifndef ELIP_H 
#define ELIP_H 

#include <scene/mesh.h>

typedef struct {
  //const mesh_t* mesh;
  vec3f_t* vertices;
  int vec_count;
  uint16_t* indices;
  int ind_count;
  uint16_t* line_indices;
  int li_count;
  
  vec3f_t radii;
  float sectors;
  float stacks;
} elip_t;

elip_t* elip_create(vec3f_t radii, int sector_count, int stack_count);

void elip_build(elip_t* elip);

void elip_free(elip_t* elip);

#endif 
