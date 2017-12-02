#ifndef OBJECT_H
# define OBJECT_H

#include <SDL2/SDL.h>

#include "map.h"

#define RATIO_LOCK_PC 4

enum state
{
  ON,
  LOCK,
  BROKE
};

enum tile_type
{
  NONE = ' ',
  PC = 'P',
  WALL = 'W',
  START = 'S',
  SPAWN = 'E'
};

struct object
{
  size_t x;
  size_t y;
  enum tile_type type;
  enum state state;
  SDL_Rect rect;
  SDL_Color color;
};

struct object *object_create(enum tile_type type, int x, int y);
void obj_delete(struct object *obj);
void print_obj(struct object *obj);

#endif /* !OBJECT_H */
