#include "map.h"
#include "object.h"
#include "player.h"

int near_lock(struct player *p, struct map *map)
{
  if (p->y != 0 && map->objs[p->x][p->y - 1] == PC
      && map->objs[p->x][p->y - 1]->state == 0)
    return 1;
  if (p->y < map->height && map->objs[p->x][p->y + 1] == PC
      && map->objs[p->x][p->y + 1]->state == 0)
    return 1;
  if (p->x != 0 && map->objs[p->x - 1][p->y] == PC
      && map->objs[p->x - 1][p->y]->state == 0)
    return 1;
  if (p->x < map->width && map->objs[p->x + 1][p->y] == PC
      && map->objs[p->x + 1][p->y]->state == 0)
    return 1;

  return 0;
}
