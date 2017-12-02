#include "msdl.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "move.h"

int player_move_up(struct player *p, struct map *map)
{
  if (p->y != 0 && (map->objs[p->x][p->y - 1]->type == NONE
      || map->objs[p->x][p->y - 1]->type == START) )
  {
    --p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_down(struct player *p, struct map *map)
{
  if (p->y + 1 < map->height && (map->objs[p->x][p->y + 1]->type == NONE
      || map->objs[p->x][p->y + 1]->type == START) )
  {
    ++p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_right(struct player *p, struct map *map)
{
  if (p->x + 1 < map->width && (map->objs[p->x + 1][p->y]->type == NONE
      || map->objs[p->x + 1][p->y]->type == START) )
  {
    ++p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_left(struct player *p, struct map *map)
{
  if (p->x != 0 && (map->objs[p->x - 1][p->y]->type == NONE
      || map->objs[p->x - 1][p->y]->type == START) )
  {
    --p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}
