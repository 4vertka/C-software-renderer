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

  elip->vec_count = (stack_count + 1) * (sector_count + 1);
  elip->ind_count = stack_count * sector_count * 6;
  elip->li_count = stack_count * sector_count * 4;

  elip->vertices = malloc(elip->vec_count * sizeof(*elip->vertices));
  elip->indices = malloc(elip->ind_count * sizeof(*elip->indices));
  elip->line_indices = malloc(elip->li_count * sizeof(*elip->line_indices));

  if (!elip->vertices || !elip->indices || !elip->line_indices) {
    elip_free(elip);
    return NULL;
  }

  elip->transform.position = position;
  elip->transform.rotation = rotation;
  elip->transform.scale = scale;

  elip->color = color;
  elip->mode = mode;

  elip_build(elip);

  return elip;
}

void elip_draw(elip_t* elip, framebuffer_t* fb, mat4x4_t view) {
  mat4x4_t model = transform_to_mat(&elip->transform);
  mat4x4_t mvp = mat4_mul_mat4(view, model);

  vec3f_t* screen = malloc(elip->vec_count * sizeof(*screen));
  for (int i = 0; i < elip->vec_count; i++) {
    vec4f_t clip = build_mvp_position(mvp, elip->vertices[i]);
    screen[i] = convert_to_ndc(clip, fb->width, fb->height);
  }

  for (int i = 0; i + 2 < elip->ind_count; i+=3) {
    vec3f_t a = screen[elip->indices[i]];
    vec3f_t b = screen[elip->indices[i+1]];
    vec3f_t c = screen[elip->indices[i+2]];

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

void elip_build(elip_t* elip) {

  memset(elip->vertices, 0, elip->vec_count * sizeof(*elip->vertices));
  memset(elip->indices, 0, elip->ind_count * sizeof(*elip->indices));
  memset(elip->line_indices, 0, elip->li_count * sizeof(*elip->line_indices));

  int v = 0;
  float x, y, z, xy;

  float sector_step = 2 * M_PI / elip->sectors;
  float stack_step = M_PI / elip->stacks;
  float sector_angle, stack_angle;

  for (int i = 0; i <= elip->stacks; ++i) {
    stack_angle = M_PI / 2 - i * stack_step;
    xy = elip->radii.x * cosf(stack_angle);
    z = elip->radii.z * sinf(stack_angle);

    for (int j = 0; j <= elip->sectors; ++j) {
      sector_angle = j * sector_step;

      x = xy * cosf(sector_angle);
      y = xy * sinf(sector_angle);
      elip->vertices[v].x = x;
      elip->vertices[v].y = y;
      elip->vertices[v].z = z;

      v++;
    }
  }

  int idx = 0;
  int lidx = 0;
  uint32_t k1, k2;
  for (int i = 0; i < elip->stacks; ++i) {
    k1 = i * (elip->sectors + 1);
    k2 = k1 + elip->sectors + 1;

    for (int j = 0; j < elip->sectors; ++j, ++k1, ++k2) {
      if (i != 0) {
        elip->indices[idx++] = k1;
        elip->indices[idx++] = k2;
        elip->indices[idx++] = k1+1;
      }
      if (i != (elip->stacks-1)) {
        elip->indices[idx++] = k1+1;
        elip->indices[idx++] = k2;
        elip->indices[idx++] = k2+1;
      }

      elip->line_indices[lidx++] = k1;
      elip->line_indices[lidx++] = k2;
      if (i != 0) {
        elip->line_indices[lidx++] = k1;
        elip->line_indices[lidx++] = k1 + 1;
      }

    }
  }
}

void elip_free(elip_t* elip) {
  free(elip->vertices);
  free(elip->indices);
  free(elip->line_indices);
  free(elip);
}
