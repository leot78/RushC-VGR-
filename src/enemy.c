#include <stdlib.h>

#include "msdl.h"
#include "enemy.h"

struct enemy *enemy_create(int x, int y, life)
{
  struct player *p = player_create(x, y, life);
  p->color = pick_color(BLACK);
  struct enemy *e = malloc(sizeof(struct enemy));
  e->player = p;
  e->last_move = NONE;
  return e;
}
/*
void move_enemy(struct enemy *e, struct map *map)
{*/
  
