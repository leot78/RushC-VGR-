#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "map.h"
#include "object.h"
#include "vector2.h"

#define RATIO_LOCK_PC 4

struct object *object_create(enum tile_type type, int state, int x, int y)
{
  struct object *obj = malloc(sizeof(struct object));

  obj->type = type;

  switch (type)
  {
    case NONE:
      obj->state = state;
      obj->rect = init_rect(
      break;
    case  WALL:
      obj->state = state;
      break;
    case PC:
      object_pc(obj);
      break;
    default:
      obj->state = 0;
  }

  return obj;
}

void obj_delete(struct object *obj)
{
  free(obj);
}

void object_pc(struct object *obj)
{
  srand(time(NULL));
  int r = rand();

  obj->state = (r % RATIO_LOCK_PC == 0);
}

void print_obj(struct object *obj)
{
  if (obj->type == PC)
  {
    if (obj->state == 0)
      printf("P");
    else
      printf("X");
  }
  else
    printf("%c", obj->type);
}
