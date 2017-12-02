#include <rand.h>
#include <stdlib.h>
#include <time.h>

#include "msdl.h"
#include "enemy.h"
#include "move.h"
#include "player.h"

struct enemy *enemy_create(int x, int y, life)
{
  struct player *p = player_create(x, y, life);
  p->color = pick_color(BLACK);
  struct enemy *e = malloc(sizeof(struct enemy));
  e->player = p;
  e->last_move = NONE;
  return e;
}

int try_move_enemy(enum move last, struct enemy *e, struct map *map)
{
  switch (last)
  {
    case UP:
      return player_move_up(e->p, map);
    case DOWN:
      return player_move_down(e->p, map);
    case LEFT:
      return player_move_left(e->p, map);
    case RIGHT:
      return player_move_right(e->p, map);
    case NONE:
      return 0;
  }
}

void move_enemy(struct enemy *e, struct map *map)
{
  int moved = try_move(e->last_move, e, map);
  if (moved)
    return;
  enum move;
  while (!moved)
  {
    move = rand() % 4;
    moved = try_move_enemy(move, e, map);
  }
  e->last_move = move;
}
