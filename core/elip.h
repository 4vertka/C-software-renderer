#ifndef ELIP_H 
#define ELIP_H 

#include <scene/mesh.h>
#include <framebuffer.h>
#include <math/matrix.h>
#include <renderer.h>

typedef struct {
  const mesh_t* mesh;
  vec3f_t* vertices;
  int vec_count;
  uint16_t* indices;
  int ind_count;
  uint16_t* line_indices;
  int li_count;

  vec3f_t radii;
  float sectors;
  float stacks;
  
  uint32_t color;
  transform_t transform;
  render_mode_e mode;
} elip_t;



elip_t* elip_create(vec3f_t radii, int sector_count, int stack_count,
                    vec3f_t position, vec3f_t rotation, vec3f_t scale,
                    uint32_t color, render_mode_e mode);

void elip_build(elip_t* elip);

void elip_draw(elip_t* elip, framebuffer_t* fb, mat4x4_t view);

void elip_free(elip_t* elip);

#endif 
