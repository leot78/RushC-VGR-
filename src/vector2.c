#include <err.h>
#include <stdlib.h>

#include "vector2.h"

struct vect2 *vect2_create(int x, int y)
{
  struct vect2 *v = malloc(sizeof(struct vect2));

  v->x = x;
  v->y = y;

  return v;
}

void vect2_delete(struct vect2 *v)
{
  free(v);
}
