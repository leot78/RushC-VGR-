#include <SDL2/SDL.h>

#include "lock.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "msdl.h"
#include "color.h"

struct mdp *g_mdp;

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


char *start_unlock(int size)
{
  g_mdp = malloc(sizeof(struct mdp));
  g_mdp->input[0] = '\0';

  SDL_StartTextInput();
  g_mdp->mdp = generate_string(size, 97, 123);
  return g_mdp->mdp;
}

void unlock_pc(struct object *obj)
{
  obj->type = ON;
  obj->color = pick_color(BLUE);
}

int unlock_pc_checker(char *s, char *mdp, int size_mdp)
{
  static int index = 0;
  if (s[0] == mdp[index])
  {
    index++;
    if (index == size_mdp)
    {
      index = 0;
      return 2;
    }
    return 1;
  }
  else
  {
    SDL_StopTextInput();
    index = 0;
    return 0;
  }
}
