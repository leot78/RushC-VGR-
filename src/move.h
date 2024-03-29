#ifndef MOVE_H
# define MOVE_H

#include <SDL2/SDL.h>

#include "map.h"

#define SIZE 32

int player_move_up(struct player *p, struct map *map);
int player_move_down(struct player *p, struct map *map);
int player_move_right(struct player *p, struct map *map);
int player_move_left(struct player *p, struct map *map);

void move(SDL_Event e, SDL_Renderer *renderer, struct map *map,
          struct player *player);

#endif /* !MOVE_H*/
