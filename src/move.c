#include "msdl.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "move.h"
#include "sprite.h"
#include "lock.h"
#include "color.h"
#include "text.h"

int player_move_up(struct player *p, struct map *map)
{
  if (p->y != 0 && (map->objs[p->x][p->y - 1]->type != PC
      && map->objs[p->x][p->y - 1]->type != WALL) )
  {
    --p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_down(struct player *p, struct map *map)
{
  if (p->y + 1 < map->height && (map->objs[p->x][p->y + 1]->type != PC
      && map->objs[p->x][p->y + 1]->type != WALL) )
  {
    ++p->y;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_right(struct player *p, struct map *map)
{
  if (p->x + 1 < map->width && (map->objs[p->x + 1][p->y]->type != PC
      && map->objs[p->x + 1][p->y]->type != WALL) )
  {
    ++p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

int player_move_left(struct player *p, struct map *map)
{
  if (p->x != 0 && (map->objs[p->x - 1][p->y]->type != PC
      && map->objs[p->x - 1][p->y]->type != WALL) )
  {
    --p->x;
    p->rect = init_rect(p->x * SIZE, p->y * SIZE, SIZE, SIZE);
    return 1;
  }
  return 0;
}

void move(SDL_Event e, SDL_Renderer *renderer, struct map *map, 
    struct player *player)
{
  int size_mdp = 3;
  static struct object *pc_lock = NULL;
  renderer = renderer;
  if(g_mdp)
  {
    if (e.type == SDL_TEXTINPUT)
      strcat(g_mdp->input, e.text.text);
    else if (e.key.keysym.sym == SDLK_RETURN)
    {
      if (!strcmp(g_mdp->mdp, g_mdp->input))
      {
        unlock_pc(pc_lock);
        player->score += 100;
      }
      else
        player->life -= 1;
      free(g_mdp->mdp);
      free(g_mdp);
      g_mdp = NULL;
    }
    else if (e.key.keysym.sym == SDLK_BACKSPACE)
    {
      free(g_mdp->mdp);
      free(g_mdp);
      g_mdp = NULL;
    }
  }
  else
  {  
    if (e.key.keysym.sym == SDLK_RIGHT)
      player_move_right(player, map);

    if (e.key.keysym.sym == SDLK_LEFT)
      player_move_left(player, map);

    if (e.key.keysym.sym == SDLK_UP)
      player_move_up(player, map);

    if (e.key.keysym.sym == SDLK_DOWN)
      player_move_down(player, map);

    if (e.key.keysym.sym == SDLK_RETURN)
    {
      pc_lock = near_lock(player, map);
      if (pc_lock)
        start_unlock(size_mdp);
    }
  }
}
