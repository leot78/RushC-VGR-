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

void player_move_up(struct player *p, struct map *map)
{
  struct vect2 *v = vect2_create(p->pos->x, p->pos->y - 1);
  if (check_vector(map, v))
    --p->pos->y;

  vect2_delete(v);
}

void player_move_down(struct player *p, struct map *map)
{
  struct vect2 *v = vect2_create(p->pos->x, p->pos->y + 1);
  if (check_vector(map, v))
    ++p->pos->y;

  vect2_delete(v);
}

void player_move_right(struct player *p, struct map *map)
{
  struct vect2 *v = vect2_create(p->pos->x + 1, p->pos->y);
  if (check_vector(map, v))
    ++p->pos->x;

  vect2_delete(v);
}

void player_move_left(struct player *p, struct map *map)
{
  struct vect2 *v = vect2_create(p->pos->x - 1, p->pos->y);
  if (check_vector(map, v))
    --p->pos->x;

  vect2_delete(v);
}
