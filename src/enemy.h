#ifndef PLAYER_H
# define PLAYER_H

#include <SDL2/SDL.h>

#include "player.h"
#include "map.h"

enum move
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE
};

struct enemy
{
  enum move last_move;
  struct player *player;
};

#endif /* !PLAYER_H*/
