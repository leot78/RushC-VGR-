#include "msdl.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "move.h"
#include "lock.h"

int player_move_up(struct player *p, struct map *map)
{
  if (p->y != 0 && (map->objs[p->x][p->y - 1]->type == NONE
      || map->objs[p->x][p->y - 1]->type == START) )
  {
    --p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_down(struct player *p, struct map *map)
{
  if (p->y + 1 < map->height && (map->objs[p->x][p->y + 1]->type == NONE
      || map->objs[p->x][p->y + 1]->type == START) )
  {
    ++p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_right(struct player *p, struct map *map)
{
  if (p->x + 1 < map->width && (map->objs[p->x + 1][p->y]->type == NONE
      || map->objs[p->x + 1][p->y]->type == START) )
  {
    ++p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_left(struct player *p, struct map *map)
{
  if (p->x != 0 && (map->objs[p->x - 1][p->y]->type == NONE
      || map->objs[p->x - 1][p->y]->type == START) )
  {
    --p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

void move(const Uint8 *state, SDL_Renderer *renderer, struct map *map, 
    struct player *player)
{
  int moved = 0;
  if (state[SDL_SCANCODE_RIGHT])
    moved = player_move_right(player, map);

  else if (state[SDL_SCANCODE_LEFT])
    moved = player_move_left(player, map);

  else if (state[SDL_SCANCODE_UP])
    moved = player_move_up(player, map);

  else if (state[SDL_SCANCODE_DOWN])
    moved = player_move_down(player, map);

  else if (state[SDL_SCANCODE_RETURN])
  {
    struct object *obj = near_lock(player, map);
    if (obj)
      unlock_pc(obj);
  }
  moved = moved;
  SDL_SetRenderDrawColor(renderer, 127, 57,  255, 255);
  SDL_RenderFillRect(renderer, &player->rect);
}
