#include "map.h"
#include "object.h"
#include "player.h"
#include "msdl.h"
#include "color.h"

int near_lock(struct player *p, struct map *map)
{
  if (p->y != 0 && map->objs[p->x][p->y - 1]->type == PC
      && map->objs[p->x][p->y - 1]->state == LOCK)
  {
    map->objs[p->x][p->y - 1]->color = pick_color(BLUE);
    map->objs[p->x][p->y - 1]->state = ON;
  }
  else if (p->y < map->height && map->objs[p->x][p->y + 1]->type == PC
      && map->objs[p->x][p->y + 1]->state == LOCK)
  {
    map->objs[p->x][p->y + 1]->color = pick_color(BLUE);
    map->objs[p->x][p->y + 1]->state = ON;
  }

  else if (p->x != 0 && map->objs[p->x - 1][p->y]->type == PC
      && map->objs[p->x - 1][p->y]->state == LOCK)
  {
    map->objs[p->x - 1][p->y]->color = pick_color(BLUE);
    map->objs[p->x - 1][p->y]->state = ON;
  }

  else if (p->x < map->width && map->objs[p->x + 1][p->y]->type == PC
      && map->objs[p->x + 1][p->y]->state == LOCK)
  {
    map->objs[p->x + 1][p->y]->color = pick_color(BLUE);
    map->objs[p->x + 1][p->y]->state = ON;
  }
  else
    return 0;


  return 1;
}
