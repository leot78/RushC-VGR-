#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "msdl.h"
#include "map.h"
#include "object.h"

#define SIZE 32

void object_pc(struct object *obj)
{
  int r = rand();
  if ((r % RATIO_LOCK_PC) == 0)
  {
    obj->color = pick_color(RED);
    obj->state = 0;
  }
  else
  {
    obj->color = pick_color(BLUE);
    obj->state = 1;
  }
}

struct object *object_create(enum tile_type type, int state, int x, int y)
{
  struct object *obj = malloc(sizeof(struct object));

  obj->type = type;

  obj->rect = init_rect(x * SIZE, y * SIZE, SIZE, SIZE);
  switch (type)
  {
    case  WALL:
      obj->state = state;
      obj->color = pick_color(GREY);
      break;
    case PC:
      object_pc(obj);
      break;
    default:
      obj->state = state;
      obj->color = pick_color(BLACK);
  }

  return obj;
}

void obj_delete(struct object *obj)
{
  free(obj);
}

void print_obj(struct object *obj)
{
  if (obj->type == PC)
  {
    if (obj->state == 1)
      printf("P");
    else
      printf("X");
  }
  else
    printf("%c", obj->type);
}
