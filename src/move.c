#include "msdl.h"
#include "map.h"
#include "object.h"
#include "player.h"

void player_move_up(struct player *p, struct map *map)
{
  if (p->y != 0 && map->objs[p->x][p->y - 1]->type == NONE)
  {
    --p->y;
    p->rect = init_rect(p->x * 16, p->y * 16, 16, 16);
  }
}

void player_move_down(struct player *p, struct map *map)
{
  if (p->y + 1 < map->height && map->objs[p->x][p->y + 1]->type == NONE)
  {
    ++p->y;
    p->rect = init_rect(p->x * 16, p->y * 16, 16, 16);
  }
}

void player_move_right(struct player *p, struct map *map)
{
  if (p->x + 1 < map->width && map->objs[p->x + 1][p->y]->type == NONE)
  {
    ++p->x;
    p->rect = init_rect(p->x * 16, p->y * 16, 16, 16);
  }
}

void player_move_left(struct player *p, struct map *map)
{
  if (p->x != 0 && map->objs[p->x - 1][p->y]->type == NONE)
  {
    --p->x;
    p->rect = init_rect(p->x * 16, p->y * 16, 16, 16);
  }
}
