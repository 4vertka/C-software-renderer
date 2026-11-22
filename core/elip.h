#ifndef ELIP_H 
#define ELIP_H 

#include <scene/mesh.h>
#include <framebuffer.h>
#include <math/matrix.h>
#include <renderer.h>

typedef struct {
  mesh_t* mesh;

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

//void elip_build(elip_t* elip);

void elip_draw(elip_t* elip, framebuffer_t* fb, mat4x4_t view, mat4x4_t proj);

void elip_free(elip_t* elip);


mesh_t* elip_mesh_create(float sector_count, float stack_count);

void elip_mesh_build(mesh_t* mesh, float sectors, float stacks, vec3f_t radii);

#endif 
