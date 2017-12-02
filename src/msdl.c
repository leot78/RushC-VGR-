#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <err.h>
#include <time.h>

#include "msdl.h"
#include "map.h"
#include "player.h"
#include "object.h"
#include "move.h"

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
  if (SDL_Init(SDL_INIT_AUDIO) < 0) 
    errx(127, "SDl audio could not initialize !");
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
  Mix_VolumeMusic(50);
  Mix_Music *music = Mix_LoadMUS("../../sounds/game.mp3");
  Mix_PlayMusic(music, 1);
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
      color.r = 200;
      color.g = 200;
      color.b = 200;
      break;

    case RED:
      color.r = 210;
      color.g = 50;
      color.b = 50;
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
      color.r = 50;
      color.g = 50;
      color.b = 210;
      break;

    case GREY:
      color.r = 127;
      color.g = 127;
      color.b = 127;
      break;
  }
  return color;
}




void render_map_block(int i, int j, struct map *map, SDL_Renderer *renderer)
{
  struct object *obj = map->objs[i][j];
  SDL_SetRenderDrawColor(renderer, obj->color.r, obj->color.g, 
      obj->color.b, 0);
  SDL_RenderFillRect( renderer, &obj->rect );
}

void render_map(struct map *map, SDL_Renderer *renderer)
{

  for (size_t j = 0; j < map->height; ++j)
  {
    for (size_t i = 0; i < map->width; ++i)
    {
      render_map_block(i, j, map, renderer);
    }
  }
}

void move(const Uint8 *state, SDL_Renderer *renderer, struct map *map, 
    struct player *player)
{
  int moved = 0;
  if(state[SDL_SCANCODE_RIGHT])
    moved = player_move_right(player, map);

  else if(state[SDL_SCANCODE_LEFT])
    moved = player_move_left(player, map);

  else if(state[SDL_SCANCODE_UP])
    moved = player_move_up(player, map);

  else if(state[SDL_SCANCODE_DOWN])
    moved = player_move_down(player, map);

  SDL_SetRenderDrawColor(renderer, 127, 57,  255, 255);
  SDL_RenderFillRect(renderer, &player->rect);
  if (moved)
    SDL_Delay(50);
}

int main(int argc, char **argv)
{
  if (argc != 2)
    return -1;

  srand(time(NULL));
  struct map *map = parse_map(argv[1]);
  init();

  TTF_Font *font = TTF_OpenFont(FONT, 172);
  if (!font)
    return -1;

  SDL_Window *screen = get_screen();

  SDL_Renderer* renderer = NULL;
  renderer =  SDL_CreateRenderer( screen, -1, SDL_RENDERER_ACCELERATED);
  int quit = 0;
  SDL_Event e;

  struct player *player =  player_create(map->start_x, map->start_y, 1);
  render_map(map, renderer);
  SDL_SetRenderDrawColor( renderer, 127, 57,  255, 255 );
  SDL_RenderFillRect( renderer, &player->rect );
  SDL_RenderPresent(renderer);
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  while (!quit)
  {
    render_map(map, renderer);
    if (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
        quit = 1;
    }
    move(state, renderer, map, player);
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
  }
  SDL_DestroyWindow(screen);

  SDL_Quit();
}
