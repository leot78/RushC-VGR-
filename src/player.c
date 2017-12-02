#include <stdlib.h>

#include "msdl.h"
#include "vector2.h"
#include "player.h"

struct player *player_create(int x, int y, int life)
{
  struct player *p = malloc(sizeof(struct player));

  p->x = x;
  p->y = y;
  p->life = life;
  p->rect = init_rect(16, 16, x * 16, y * 16);
  p->color = pick_color(RED);
  return p;
}

void player_delete(struct player *p)
{
  vect2_delete(p->pos);
  free(p);
}

