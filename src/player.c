#include <stdlib.h>
#include <SDL2/SDL.h>

#include "msdl.h"
#include "player.h"
#include "color.h"

#define SIZE 32

struct player *player_create(int x, int y, int life)
{
  struct player *p = malloc(sizeof(struct player));

  p->x = x;
  p->y = y;
  p->life = life;
  p->rect = init_rect(x * SIZE, y* SIZE, SIZE, SIZE);
  p->color = pick_color(RED);
  return p;
}

void collision(struct **enemies, struct player *player, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    if (enemies[i]->p->x == player->x && enemies[i]->p->y == player->y)
    {
      player->life -= 1;
      return;
    }
}

void player_delete(struct player *p)
{
  free(p);
}
