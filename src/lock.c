#include <SDL2/SDL.h>

#include "lock.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "msdl.h"
#include "color.h"

struct object *near_lock(struct player *p, struct map *map)
{
  if (p->y != 0 && map->objs[p->x][p->y - 1]->type == PC
      && map->objs[p->x][p->y - 1]->state == LOCK)
    return map->objs[p->x][p->y - 1];
  else if (p->y < map->height && map->objs[p->x][p->y + 1]->type == PC
      && map->objs[p->x][p->y + 1]->state == LOCK)
    return map->objs[p->x][p->y + 1];
  else if (p->x != 0 && map->objs[p->x - 1][p->y]->type == PC
      && map->objs[p->x - 1][p->y]->state == LOCK)
    return map->objs[p->x - 1][p->y];
  else if (p->x < map->width && map->objs[p->x + 1][p->y]->type == PC
      && map->objs[p->x + 1][p->y]->state == LOCK)
    return map->objs[p->x + 1][p->y];
  else
    return NULL;
}


char *unlock_pc(struct object *pc)
{
  char *mdp = generate_string(10, 97, 123);
  pc->state = ON;
  pc->color = pick_color(BLUE);
  return mdp;
}
