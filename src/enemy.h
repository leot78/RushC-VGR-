#ifndef ENEMY_H
# define ENEMY_H

#include <SDL2/SDL.h>

#include "player.h"
#include "map.h"
#include "msdl.h"

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
  int speed;
  int cpt;
};

struct enemy *enemy_create(int x, int y, int life, int speed);
struct enemy **enemy_create_all(struct object *spawns[MAX_SPAWN],
                                size_t number, int speed);
void enemy_delete(struct enemy *e);
void move_enemy(struct enemy *e, struct map *map, SDL_Renderer *renderer);
void move_all_enemies(struct enemy **enemies, size_t number, struct map *map, 
                      SDL_Renderer *renderer);

#endif /* !ENEMY_H*/
