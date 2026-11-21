#include "renderer.h"

#define MAX_MESH_VERTICES     1000

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

void object_draw(const object_t* object, framebuffer_t* fb, mat4x4_t view) {
  const mesh_t* mesh = object->mesh;
  mat4x4_t model = transform_to_mat(&object->transform);
  mat4x4_t mvp = mat4_mul_mat4(view, model);

  vec3f_t screen[MAX_MESH_VERTICES];
  for (int i = 0; i < mesh->vec_count; i++) {
    vec4f_t clip = build_mvp_position(mvp, mesh->vertices[i]);
    screen[i] = convert_to_ndc(clip, fb->width, fb->height);
  }
  
  for (int i = 0; i + 2 < mesh->ind_count; i+=3) {
    vec3f_t a = screen[mesh->indices[i]];
    vec3f_t b = screen[mesh->indices[i+1]];
    vec3f_t c = screen[mesh->indices[i+2]];

    switch (object->mode) {
      case RENDER_FILLED:
        plot_triangle(fb, a, b, c, object->color);
        break;
      case RENDER_WIREFRAME:
        plot_triangle_wireframe(fb, a, b,c, object->color);
        break;
    }

    //plot_triangle(fb, screen[i], screen[i+1], screen[i+2], object->color);
  }
}
