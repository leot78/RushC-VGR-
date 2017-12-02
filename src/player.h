#ifndef PLAYER_H
# define PLAYER_H

#include <SDL2/SLD.h>

#include "vector2.h"

struct player
{
  int x;
  int y;
  size_t life;
  SDL_Rect rect;
  SDL_Color color;
};

struct player *player_create(int x, int y, int life);
void player_delete(struct player *p);

void player_move_up(struct player *p, struct map *map);
void player_move_down(struct player *p, struct map *map);
void player_move_right(struct player *p, struct map *map);
void player_move_left(struct player *p, struct map *map);

#endif /* !PLAYER_H */
