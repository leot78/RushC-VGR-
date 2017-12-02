#ifndef OBJECT_H
# define OBJECT_H

#include <SDL2/SDL.h>

#include "map.h"
#include "vector2.h"

#define RATIO_LOCK_PC 4

enum tile_type
{
  NONE = ' ',
  PC = 'P',
  WALL = 'W'
};

struct object
{
  enum tile_type type;
  unsigned state;
  struct vect2 *pos;
  SDL_Rect rect;
  SDL_Color color;
};

struct object *object_create(enum tile_type type, int state, int x, int y);
void obj_delete(struct object *obj);
void print_obj(struct object *obj);

#endif /* !OBJECT_H */
