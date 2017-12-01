#ifndef OBJECT_H
# define OBJECT_H

#include "map.h"
#include "vector2.h"

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
};

struct object *object_create(enum tile_type type, int state);
void obj_delete(struct object *obj);
void print_obj(struct object *obj);

#endif /* !OBJECT_H */
