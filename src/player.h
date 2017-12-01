#ifndef PLAYER_H
# define PLAYER_H

#include "vector2.h"

struct player
{
  struct vect2 *pos;
  size_t life;
};

struct player *player_create(int x, int y, int life);
void player_delete(struct player *p);

#endif /* !PLAYER_H */
