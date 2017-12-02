#include "msdl.h"
#include "map.h"
#include "object.h"
#include "player.h"

#define SIZE 32

void player_move_up(struct player *p, struct map *map)
{
  if (p->y != 0) 
  {
    struct object *obj = map->objs[p->x][p->y - 1];
    if (obj->type == NONE)
    {
      --p->y;
      p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    }
    else if (obj->type == PC && obj->state == 0)
      obj->color = pick_color(BLUE);
  }
}

void player_move_down(struct player *p, struct map *map)
{
  if (p->y + 1 < map->height && map->objs[p->x][p->y + 1]->type == NONE)
  {
    ++p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
  }
}

void player_move_right(struct player *p, struct map *map)
{
  if (p->x + 1 < map->width && map->objs[p->x + 1][p->y]->type == NONE)
  {
    ++p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
  }
}

void player_move_left(struct player *p, struct map *map)
{
  if (p->x != 0 && map->objs[p->x - 1][p->y]->type == NONE)
  {
    --p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
  }
}
