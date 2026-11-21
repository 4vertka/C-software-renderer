#ifndef SCENE_H 
#define SCENE_H

#include <object.h>

#define MAX_OBJECTS 100

typedef struct {
  object_t objects[MAX_OBJECTS];
  int count;
} scene_h;

#endif 
