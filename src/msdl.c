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
#include "lock.h"
#include "text.h"
#include "color.h"
#include "enemy.h"

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

SDL_Rect init_rect(int x, int y, int w, int h)
{
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  return rect;
}

void render_map(struct map *map, SDL_Renderer *renderer)
{

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
}

int in_rect(SDL_Rect rec)
{
  int x = 0;
  int y = 0;
  int rx = rec.x;
  int ry = rec.y;
  int rw = rec.w;
  int rh = rec.h;
  SDL_GetMouseState(&x, &y);
  return x > rx && x < rx + rw && y > ry && y < ry + rh;
}

int title(void)
{
  SDL_Window *screen = get_screen();
  SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 
                                              SDL_RENDERER_ACCELERATED);
  int quit = 0;
  SDL_Event e;
  SDL_Rect txt_rect = init_rect(430,100,400,100);
  SDL_Rect start_rect = init_rect(430, 300, 400, 100);
  SDL_Rect exit_rect = init_rect(430, 500, 400, 100);

  
  while (!quit)
  {
    if (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(start_rect))
      {
        printf("START");
        quit = 1;
      }
      if (e.type == SDL_QUIT 
          || (e.type == SDL_MOUSEBUTTONDOWN && in_rect(exit_rect)))
        quit = 127;
    }
    render_text("(Un)Lock Legacy", pick_color(BLUE), renderer, txt_rect);
    render_text("Start", pick_color(BLACK), renderer, start_rect);
    render_text("Exit", pick_color(BLACK), renderer, exit_rect);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  return quit;
}

int play(char *map_p)
{

  struct map *map = parse_map(map_p);
  SDL_Window *screen = get_screen();
  SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 
                                              SDL_RENDERER_ACCELERATED);
  int quit = 0;
  SDL_Event e;
  struct player *player =  player_create(map->start_x, map->start_y, 1);
  struct enemy **enemies = enemy_create_all(map->spawns, 10);
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
    move_all_enemies(enemies, 10, map, renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(60);
  }
  SDL_DestroyRenderer(renderer);
  free(player);
  return 0;
}

int level_choice(void)
{
  SDL_Window *screen = get_screen();
  SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 
                                              SDL_RENDERER_ACCELERATED);
  int quit = 0;
  SDL_Event e;
  SDL_Rect sr_rect = init_rect(430,100,400,100);
  SDL_Rect past_rect = init_rect(430, 300, 400, 100);
  SDL_Rect vj_rect = init_rect(430, 500, 400, 100);
  SDL_Rect mid_rect = init_rect(430, 800, 400, 100);
  
  while (!quit)
  {
    if (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(sr_rect))
        quit = 2;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(past_rect))
        quit = 3;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(vj_rect))
        quit = 4;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(mid_rect))
        quit = 5;
      if (e.type == SDL_QUIT)
        quit = 127;
    }
    render_text("LabSR_SM14", pick_color(BLUE), renderer, sr_rect);
    render_text("Pasteur", pick_color(BLACK), renderer, past_rect);;
    render_text("Villejuif", pick_color(BLACK), renderer, vj_rect);
    render_text("MidLab", pick_color(BLACK), renderer, mid_rect);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  return quit;
}

void game(void)
{
  int menu = 0;
  while (menu != 127)
  {
    if (menu == 0)
      menu = title();
    else if (menu == 1)
      menu = level_choice();
    else if (menu == 2)
      menu = play("../../maps/LabSR_SM14.map");
    else if (menu == 3)
      menu = play("../../maps/pasteur.map");
    else if (menu == 4)
      menu = play("../../maps/VJ.map");
    else if (menu == 5)
      menu = play("../../maps/midlab.map");
  }
}

int main(void)
{
  srand(time(NULL));
  init();
  SDL_Window *screen = get_screen();
  game();
  SDL_DestroyWindow(screen);

  SDL_Quit();
}
