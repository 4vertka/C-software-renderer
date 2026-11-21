#ifndef RENDERER_H
#define RENDERER_H 

#include <stdint.h>

#include "math/vector.h"
#include "math/matrix.h"
#include <framebuffer.h>
#include <raster.h>












mat4x4_t build_model_mat(float angle, vec3f_t axis);
mat4x4_t build_view_mat(vec3f_t pos);
mat4x4_t build_projection_mat(float fov, float aspect, float near, float far);
mat4x4_t build_mvp_mat(mat4x4_t proj, mat4x4_t view, mat4x4_t model);

vec4f_t build_mvp_position(mat4x4_t mvp, vec3f_t pos);
vec4f_t build_color(vec3f_t color);

vec3f_t convert_to_ndc(vec4f_t clip, int w, int h);

mesh_t* mesh_init(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count);
void mesh_draw(framebuffer_t* fb, mesh_t* m, mat4x4_t mvp, uint32_t color);
int mesh_get_count(void);
mesh_t* mesh_get(int index);
void mesh_init_default(mesh_t* mesh);

#endif 
