#include <stdlib.h>
#include <time.h>

#include "msdl.h"
#include "enemy.h"
#include "move.h"
#include "player.h"
#include "color.h"

void move_all_enemies(struct enemy **enemies, size_t number, struct map *map, 
                      SDL_Renderer *renderer)
{
  for (size_t i = 0; i < number; i++)
    move_enemy(enemies[i], map, renderer);
}

struct enemy *enemy_create(int x, int y, int life)
{
  struct player *p = player_create(x, y, life);
  p->color = pick_color(BLACK);
  struct enemy *e = malloc(sizeof(struct enemy));
  e->p = p;
  e->last_move = NONE;
  return e;
}

struct enemy **enemy_create_all(struct object *spawns[MAX_SPAWN], size_t number)
{
  struct enemy **enemies = malloc(sizeof(struct enemy *) * number);
  for (size_t i = 0; i < number; i++)
  {
    struct object *obj = spawns[i % MAX_SPAWN];
    enemies[i] = enemy_create(obj->x, obj->y, 1);
  }
  return enemies;
}

void enemy_delete(struct enemy *e)
{
  player_delete(e->p);
  free(e);
}

int try_move_enemy(enum move last, struct enemy *e, struct map *map)
{
  switch (last)
  {
    case UP:
      return player_move_up(e->p, map);
    case DOWN:
      return player_move_down(e->p, map);
    case LEFT:
      return player_move_left(e->p, map);
    case RIGHT:
      return player_move_right(e->p, map);
    default:
      return 0;
  }
}

void move_enemy(struct enemy *e, struct map *map, SDL_Renderer *renderer)
{
  int moved = try_move_enemy(e->last_move, e, map);
  if (!moved)
  {
    enum move last_move;
    while (!moved)
    {
      last_move = rand() % 4;
      moved = try_move_enemy(last_move, e, map);
    }
    e->last_move = last_move;
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(renderer, &e->p->rect);
}
