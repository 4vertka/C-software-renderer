#include "elip.h"
#include <string.h>
#include <stdlib.h>

#define MAX_ELIP_VERTICES 1000

elip_t* elip_create(vec3f_t radii, int sector_count, int stack_count,
                    vec3f_t position, vec3f_t rotation, vec3f_t scale,                
                    uint32_t color, render_mode_e mode) {                              

  elip_t* elip = malloc(sizeof(*elip));
  if (!elip) return NULL; 

  elip->radii = radii;
  elip->sectors = sector_count;
  elip->stacks = stack_count;

  mesh_t* mesh = elip_mesh_create(sector_count, stack_count);
  elip_mesh_build(mesh, sector_count, stack_count, radii);
  elip->mesh = mesh;
  
  elip->transform.position = position;
  elip->transform.rotation = rotation;
  elip->transform.scale = scale;

  elip->color = color;
  elip->mode = mode;

  return elip;
}

void elip_draw(elip_t* elip, framebuffer_t* fb, mat4x4_t view, mat4x4_t proj) {                           
  mat4x4_t model = transform_to_mat(&elip->transform);                   
  mat4x4_t mv = mat4_mul_mat4(view, model);
  mat4x4_t mvp = mat4_mul_mat4(proj, mv);                                               
                                                                                           
  vec3f_t* screen = malloc(elip->mesh->vec_count * sizeof(*screen));                             
  for (int i = 0; i < elip->mesh->vec_count; i++) {                                              
    vec4f_t clip = build_mvp_position(mvp, elip->mesh->vertices[i]);                             
    screen[i] = convert_to_ndc(clip, fb->width, fb->height);                               
  }                                                                                        
                                                                                           
  for (int i = 0; i + 2 < elip->mesh->ind_count; i+=3) {                                         
    vec3f_t a = screen[elip->mesh->indices[i]];                                                  
    vec3f_t b = screen[elip->mesh->indices[i+1]];                                                
    vec3f_t c = screen[elip->mesh->indices[i+2]];                                                
                                                                                           
    float visibility = black_face_culling(a, b, c);                                        
    if (visibility < 0.0f) continue;                                                       
                                                                                           
    switch (elip->mode) {                                                                  
      case RENDER_FILLED:                                                                  
        plot_triangle(fb, a, b, c, elip->color);                                           
        break;                                                                             
      case RENDER_WIREFRAME:                                                               
        plot_triangle_wireframe(fb, a, b, c, elip->color);                                 
        break;                                                                             
    }                                                                                      
  }                                                                                        
                                                                                           
  free(screen);                                                                            
}                                                                                          

mesh_t* elip_mesh_create(float sector_count, float stack_count) {
  mesh_t* mesh = malloc(sizeof(*mesh));

  mesh->vec_count = (stack_count + 1) * (sector_count + 1);                            
  mesh->ind_count = stack_count * sector_count * 6;                                    
  mesh->li_count = stack_count * sector_count * 4;                                     
                                                                                   
  mesh->vertices = malloc(mesh->vec_count * sizeof(*mesh->vertices));                  
  mesh->indices = malloc(mesh->ind_count * sizeof(*mesh->indices));                    
  mesh->line_indices = malloc(mesh->li_count * sizeof(*mesh->line_indices));           
                                                                                       
  if (!mesh->vertices || !mesh->indices || !mesh->line_indices) {                      
    mesh_free(mesh);
    return NULL;                                                                       
  }                                                                                    

  return mesh;
}

void elip_mesh_build(mesh_t* mesh, float sectors, float stacks, vec3f_t radii) {

  memset(mesh->vertices, 0, mesh->vec_count * sizeof(*mesh->vertices));          
  memset(mesh->indices, 0, mesh->ind_count * sizeof(*mesh->indices));            
  memset(mesh->line_indices, 0, mesh->li_count * sizeof(*mesh->line_indices));   

  int v = 0;                                                                                                
  float x, y, z, xy;                                                                                        
                                                                                                            
  float sector_step = 2 * M_PI / sectors;                                                             
  float stack_step = M_PI / stacks;                                                                   
  float sector_angle, stack_angle;                                                                          
                                                                                                            
  for (int i = 0; i <= stacks; ++i) {                                                                 
    stack_angle = M_PI / 2 - i * stack_step;                                                                
    xy = radii.x * cosf(stack_angle);                                                                 
    z = radii.z * sinf(stack_angle);                                                                  
                                                                                                            
    for (int j = 0; j <= sectors; ++j) {                                                              
      sector_angle = j * sector_step;                                                                       
                                                                                                            
      x = xy * cosf(sector_angle);                                                                          
      y = xy * sinf(sector_angle);                                                                          
      mesh->vertices[v].x = x;                                                                              
      mesh->vertices[v].y = y;                                                                              
      mesh->vertices[v].z = z;                                                                              
                                                                                                            
      v++;                                                                                                  
    }                                                                                                       
  }                                                                                                         
                                                                                                            
  int idx = 0;                                                                                              
  int lidx = 0;                                                                                             
  uint32_t k1, k2;                                                                                          
  for (int i = 0; i < stacks; ++i) {                                                                  
    k1 = i * (sectors + 1);                                                                           
    k2 = k1 + sectors + 1;                                                                            
                                                                                                            
    for (int j = 0; j < sectors; ++j, ++k1, ++k2) {                                                   
      if (i != 0) {                                                                                         
        mesh->indices[idx++] = k1;                                                                          
        mesh->indices[idx++] = k2;                                                                          
        mesh->indices[idx++] = k1+1;                                                                        
      }                                                                                                     
      if (i != (stacks-1)) {                                                                          
        mesh->indices[idx++] = k1+1;                                                                        
        mesh->indices[idx++] = k2;                                                                          
        mesh->indices[idx++] = k2+1;                                                                        
      }                                                                                                     
                                                                                                            
      mesh->line_indices[lidx++] = k1;                                                                      
      mesh->line_indices[lidx++] = k2;                                                                      
      if (i != 0) {                                                                                         
        mesh->line_indices[lidx++] = k1;                                                                    
        mesh->line_indices[lidx++] = k1 + 1;                                                                
      }                                                                                                     
                                                                                                            
    }                                                                                                       
  }                                                                                                         

}

void elip_free(elip_t* elip) {
  mesh_free(elip->mesh);
  free(elip);
}
