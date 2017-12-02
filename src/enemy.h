#ifndef ENEMY_H
# define ENEMY_H

#include <SDL2/SDL.h>

#include "player.h"
#include "map.h"

enum move
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NO
};

struct enemy
{
  enum move last_move;
  struct player *p;
};

struct enemy *enemy_create(int x, int y, int life);
void enemy_delete(struct enemy *e);
void move_enemy(struct enemy *e, struct map *map, SDL_Renderer *renderer);

#endif /* !ENEMY_H*/
