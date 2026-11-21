#include "renderer.h"

static mesh_t meshes[255];
static int mesh_count = 0;

vec3f_t convert_to_ndc(vec4f_t clip, int w, int h) {
  vec3f_t res;
  
  float inv_w = 1/clip.w;
  float x_w = clip.x * inv_w;
  float y_w = clip.y * inv_w;
  float z_w = clip.z * inv_w;

  res.x = (x_w + 1.0f) * 0.5f * w;
  res.y = (1.0f - y_w) * 0.5f * h;
  res.z = 0.0 + z_w * (1.0 - 0.0);

  return res;
}

mat4x4_t build_model_mat(float angle, vec3f_t axis) {                                                 
  mat4x4_t model = mat4_create(1.0f);                                                                 
  model = mat4_rotate(model, angle, axis);                                                            
                                                                                                      
  return model;                                                                                       
}                                                                                                     
                                                                                                      
mat4x4_t build_view_mat(vec3f_t pos) {                                                                
  mat4x4_t view = mat4_create(1.0f);                                                                  
  view = mat4_translation(view, pos);                                                                 
                                                                                                      
  return view;                                                                                        
}                                                                                                     
                                                                                                      
mat4x4_t build_projection_mat(float fov, float aspect, float near, float far) {                       
  mat4x4_t proj = mat4_perspective(fov, aspect, near, far);                                           
                                                                                                      
  return proj;                                                                                        
}                                                                                                     
                                                                                                      
mat4x4_t build_mvp_mat(mat4x4_t proj, mat4x4_t view, mat4x4_t model) {                                
  mat4x4_t mvp = mat4_mul_mat4(mat4_mul_mat4(proj, view), model);                                     
                                                                                                      
  return mvp;                                                                                         
}                                                                                                     
                                                                                                      
vec4f_t build_mvp_position(mat4x4_t mvp, vec3f_t pos) {                                                   
  vec4f_t position = mat4_mul_vec4(mvp, (vec4f_t){pos.x, pos.y, pos.z, 1.0f});                        
                                                                                                      
  return position;                                                                                    
}          

vec4f_t build_color(vec3f_t color) {
  return (vec4f_t) {color.x, color.y, color.z, 1.0f};
}

mesh_t* mesh_init(vec3f_t* vertices, int vec_count, uint16_t* indices, int ind_count) {
  mesh_t* mesh = &meshes[mesh_count];

  mesh->vertices = vertices;
  mesh->indices = indices;
  mesh->vec_count = vec_count;
  mesh->ind_count = ind_count;
  
  mesh_init_default(mesh);

  mesh_count++;

  return mesh;
}

void mesh_init_default(mesh_t* mesh) {
 // mesh->rotation = (vec3f_t){0,0,0};
  //mesh->angle = -55.0;
  //mesh->scale = (vec3f_t){1,1,1};
  //mesh->translation = (vec3f_t){0,0,0};
}

void mesh_draw(framebuffer_t* fb, mesh_t* m, mat4x4_t mvp, uint32_t color) {
  vec3f_t screen[m->vec_count];
  for (int i = 0; i < m->ind_count; i++) {
    vec4f_t clip = build_mvp_position(mvp, m->vertices[m->indices[i]]);

    vec3f_t res = convert_to_ndc(clip, fb->width, fb->height);

    screen[i] = res;
  }

  for (int i = 0; i < m->ind_count-2; i++) {
    int f = i;
    int s = ++i;
    int t = ++i;
    plot_triangle(fb, screen[f], screen[s], screen[t], color);
  }
}

int mesh_get_count(void) {
  return mesh_count;
}

mesh_t* mesh_get(int index) {
  return &meshes[index];
}
