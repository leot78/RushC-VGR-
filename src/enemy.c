#include <stdlib.h>
#include <time.h>

#include "msdl.h"
#include "enemy.h"
#include "move.h"
#include "player.h"
#include "color.h"
#include "sprite.h"

void move_all_enemies(struct enemy **enemies, size_t number, struct map *map, 
                      SDL_Renderer *renderer)
{
  for (size_t i = 0; i < number; i++)
    move_enemy(enemies[i], map, renderer);
}

struct enemy *enemy_create(int x, int y, int life, int speed)
{
  struct player *p = player_create(x, y, life);
  p->color = pick_color(BLACK);
  struct enemy *e = malloc(sizeof(struct enemy));
  e->p = p;
  e->last_move = NONE;
  e->speed = speed;
  e->cpt = speed;
  return e;
}

struct enemy **enemy_create_all(struct object *spawns[MAX_SPAWN],
                                size_t number, int speed)
{
  struct enemy **enemies = malloc(sizeof(struct enemy *) * number);
  for (size_t i = 0; i < number; i++)
  {
    struct object *obj = spawns[i % MAX_SPAWN];
    enemies[i] = enemy_create(obj->x, obj->y, 1, speed);
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

int try_random_move(struct enemy *e, struct map *map, enum move *last_move,
                    enum move trying_move)
{
  *last_move = trying_move;
  int random = rand() % 2;
  if (random)
    *last_move = e->last_move;
  return try_move_enemy(*last_move, e, map);
}

int wall_or_pc(struct object *obj)
{
  return obj->type == PC || obj->type == WALL;
}

int move_row(struct enemy *e, struct map *map, enum move *last_move)
{
  int x = e->p->x;
  int y = e->p->y;
  struct object ***obj = map->objs;
  if (obj[x + 1][y]->type == PC || obj[x - 1][y]->type == PC
      || obj[x][y + 1]->type == PC || obj[x][y - 1]->type == PC)
    return 0;

  if (wall_or_pc(obj[x + 1][y + 1]) && wall_or_pc(obj[x - 1][y + 1])
      //&& !wall_or_pc(obj[x + 1][y - 1]) && !wall_or_pc(obj[x - 1][y - 1])
      && e->last_move != UP)
          return try_random_move(e, map, last_move, DOWN);
  
  if (wall_or_pc(obj[x + 1][y + 1]) //&& !wall_or_pc(obj[x - 1][y + 1])
      && wall_or_pc(obj[x + 1][y - 1]) //&& !wall_or_pc(obj[x - 1][y - 1])
      && e->last_move != LEFT)
    return try_random_move(e, map, last_move, RIGHT);
  
  if (/*!wall_or_pc(obj[x + 1][y + 1]) &&*/ wall_or_pc(obj[x - 1][y + 1])
      && /*!wall_or_pc(obj[x + 1][y - 1]) &&*/ wall_or_pc(obj[x - 1][y - 1])
      && e->last_move != RIGHT)
    return try_random_move(e, map, last_move, LEFT);
  
  if (//!wall_or_pc(obj[x + 1][y + 1]) && !wall_or_pc(obj[x - 1][y + 1])
       wall_or_pc(obj[x + 1][y - 1]) && wall_or_pc(obj[x - 1][y - 1])
      && e->last_move != DOWN)
    return try_random_move(e, map, last_move, UP);
  return 0;
}

void move_enemy(struct enemy *e, struct map *map, SDL_Renderer *renderer)
{
  if (e->cpt == e->speed)
  {
    enum move last_move = NO;
    int moved = move_row(e, map, &last_move);
    if (!moved)
    {
      moved = try_move_enemy(e->last_move, e, map);
      if (!moved)
      {
        while (!moved)
        {
          last_move = rand() % 4;
          moved = try_move_enemy(last_move, e, map);
        }
        e->last_move = last_move;
      }
      e->cpt = 0;
    }
  }
  else
    e->cpt++;
  print_sprite(ACU, e->p->rect, renderer);
}
