#ifndef PLAYER_H
# define PLAYER_H

#include <SDL2/SDL.h>

#include "map.h"
#include "enemy.h"

struct player
{
  size_t x;
  size_t  y;
  int life;
  SDL_Rect rect;
  SDL_Color color;
};

struct player *player_create(int x, int y, int life);
void player_delete(struct player *p);

struct object *near_lock(struct player *p, struct map *map);
#endif /* !PLAYER_H */
