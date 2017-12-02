#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <err.h>
#include <time.h>

#include "msdl.h"
#include "map.h"
#include "player.h"
#include "object.h"

SDL_Window* get_screen(void)
{
  static SDL_Window* screen = NULL;
  if (!screen)
    screen = SDL_CreateWindow("(Un)Lock Legacy", SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  return screen;
}

void init(void)
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    errx(127, "SDL could not initialize !");
  if( TTF_Init() == -1 ) 
    errx(127, "TTF could not initialize !");
}

SDL_Texture *msg_texture(TTF_Font *font, char *text, SDL_Color color, 
                        SDL_Renderer *renderer)
{
  SDL_Surface *text_surface = TTF_RenderText_Solid(font, text,color);
  SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, text_surface);
  return message;
}

SDL_Rect init_rect(int x, int y, int w, int h)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}

void render_rec(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color)
{
  SDL_SetRenderDrawColor( renderer, color.r , color.g, color.b, color.a);
  SDL_RenderFillRect( renderer, rect );
}

SDL_Color pick_color(enum colors c)
{

  SDL_Color color = {0, 0 ,0 ,0}; 
  switch(c)
  {
    case BLACK:
      color.r = 255;
      color.g = 255;
      color.b = 255;
      break;

    case RED:
      color.r = 255;
      color.g = 0;
      color.b = 0;
      break;

    case WHITE:
      color.r = 0;
      color.g = 0;
      color.b = 0;
      break;

    case GREEN:
      color.r = 0;
      color.g = 255;
      color.b = 0;
      break;

    case BLUE:
      color.r = 0;
      color.g = 0;
      color.b = 255;
      break;

    case GREY:
      color.r = 127;
      color.g = 127;
      color.b = 127;
      break;
  }
  return color;
}

void move(SDL_Event e, SDL_Renderer *renderer, struct map *map, 
          struct player *p)
{
  switch( e.key.keysym.sym )
  {
    case SDLK_UP:
      player_move_up(p, map);
      SDL_RenderFillRect( renderer, &p->rect);
      break;

    case SDLK_DOWN:
      player_move_down(p, map);
      SDL_RenderFillRect( renderer, &p->rect);
      break;

    case SDLK_LEFT:
      player_move_left(p, map);
      SDL_RenderFillRect( renderer, &p->rect);
      break;

    case SDLK_RIGHT:
      player_move_right(p, map);
      SDL_RenderFillRect( renderer, &p->rect);
      break;

    default:
      break;
  }
}

int is_moving(SDL_Event e)
{
  if(e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN ||
      e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
    return 1;
  return 0;
}
int main(int argc, char **argv)
{
  if (argc != 2)
    return -1;
  
  struct map *map = parse_map(argv[1]);
  init();
  srand(time(NULL));

  TTF_Font *font = TTF_OpenFont(FONT, 172);
  if (!font)
    return -1;

  SDL_Window *screen = get_screen();

  SDL_Renderer* renderer = NULL;
  renderer =  SDL_CreateRenderer( screen, -1, SDL_RENDERER_ACCELERATED);
  int quit = 0;
  SDL_Event e;

  //SDL_Texture *message = msg_texture(font, "(Un)Lock Legacy", BLACK, renderer);

  //SDL_Rect Message_rect = init_rect(100, 0, 400, 100);
  SDL_Rect r =  init_rect(16, 16, 16, 16);
  struct player *player =  player_create(1, 1, 1);
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);


  //SDL_RenderCopy(renderer, message, NULL, &Message_rect);

  for (size_t j = 0; j < map->height; ++j)
  {
    for (size_t i = 0; i < map->width; ++i)
    {
      struct object *obj = map->objs[i][j];
      SDL_SetRenderDrawColor(renderer, obj->color.r, obj->color.g, 
          obj->color.b, 0);
      SDL_RenderFillRect( renderer, &obj->rect );
    }
  }
  SDL_SetRenderDrawColor( renderer, 255, 0, 255, 255 );
  SDL_RenderFillRect( renderer, &r );
  //SDL_RenderFillRect(renderer, Message_rect);
  SDL_RenderPresent(renderer);
  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
        quit = 1;

      else if( e.type == SDL_KEYDOWN && is_moving(e))
      {
        struct object *obj = map->objs[player->x][player->y];
        SDL_SetRenderDrawColor(renderer, obj->color.r, obj->color.g, 
            obj->color.b, 0);
        SDL_RenderFillRect( renderer, &obj->rect );
        SDL_SetRenderDrawColor( renderer, 255, 0, 255, 255 );
        move(e, renderer, map, player);
        SDL_RenderPresent(renderer);
      }
      SDL_Delay(20);
    }
    SDL_Delay(20);
  }
  SDL_DestroyWindow(screen);

  SDL_Quit();
}
