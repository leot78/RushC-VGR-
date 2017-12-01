#include <stdlib.h>

#include "vector2.h"
#include "player.h"

struct player *player_create(int x, int y, int life)
{
  struct player *p = malloc(sizeof(struct player));

  p->pos = vect2_create(x, y);
  p->life = life;

  return p;
}

void player_delete(struct player *p)
{
  vect2_delete(p->pos);
  free(p);
}
