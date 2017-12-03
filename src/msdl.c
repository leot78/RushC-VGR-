#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
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
#include "sprite.h"

SDL_Window* get_screen(void)
{
  static SDL_Window* screen = NULL;
  if (!screen)
    screen = SDL_CreateWindow("(Un)Lock Legacy", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  return screen;
}

SDL_Renderer *get_renderer(void)
{
  static SDL_Renderer *renderer = NULL;
  if (!renderer)
    renderer = SDL_CreateRenderer(get_screen(), -1, 
      SDL_RENDERER_ACCELERATED);
  return renderer;
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
      if (obj->type == NONE || obj->type == SPAWN || obj->type == START)
        print_sprite(GROUND, obj->rect, renderer);

      if (obj->type == PC && obj->state == ON)
        print_sprite(PCULOCK, obj->rect, renderer);
      if (obj->type == PC && obj->state == LOCK)
        print_sprite(PCLOCK, obj->rect, renderer);
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

int win(void)
{
  SDL_Renderer* renderer = get_renderer();
  SDL_RenderClear(renderer);
  int quit = 0;
  SDL_Event e;
  SDL_Rect txt_rect = init_rect(430,100,400,100);
  SDL_Rect txt2_rect = init_rect(430, 500, 400, 100);

  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT || (e.key.type == SDL_KEYDOWN 
          && e.key.keysym.sym == SDLK_RETURN))
        quit = 127;
    }
    render_text("You won against the ACU's !", pick_color(RED), renderer, txt_rect);
    render_text("Press enter to replay", pick_color(BLACK), renderer, 
                txt2_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  return 0;
}

int die(int menu)
{
  SDL_Renderer* renderer = get_renderer();
  SDL_RenderClear(renderer);
  int quit = -1;
  SDL_Event e;
  SDL_Rect txt_rect = init_rect(430,100,400,100);
  SDL_Rect txt2_rect = init_rect(430, 500, 400, 100);
  SDL_Rect txt3_rect = init_rect(430, 700, 400, 100);

  while (quit == -1)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT || (e.key.type == SDL_KEYDOWN 
          && e.key.keysym.sym == SDLK_ESCAPE))
        quit = 0;
      if (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
        quit = menu - 10;
    }
    render_text("You've been confloosed", pick_color(RED), renderer, txt_rect);
    render_text("Press enter to replay", pick_color(BLACK), renderer, 
                txt2_rect);
    render_text("Press escape for menu", pick_color(BLACK), renderer, 
                txt3_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  return quit;
}

int title(void)
{
  SDL_Renderer* renderer = get_renderer();
  SDL_RenderClear(renderer);
  int quit = 0;
  SDL_Event e;
  SDL_Rect txt_rect = init_rect(430,100,400,100);
  SDL_Rect start_rect = init_rect(430, 300, 400, 100);
  SDL_Rect exit_rect = init_rect(430, 500, 400, 100);

  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(start_rect))
      {
        printf("START");
        quit = 1;
      }
      if (e.type == SDL_QUIT 
          || (e.type == SDL_MOUSEBUTTONDOWN && in_rect(exit_rect)))
        quit = 127;

      if (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        quit = 127;
    }
    render_text("(Un)Lock Legacy", pick_color(BLUE), renderer, txt_rect);
    render_text("Start", pick_color(BLACK), renderer, start_rect);;
    render_text("Exit", pick_color(BLACK), renderer, exit_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
  return quit;
}


int play(char *map_p, int menu)
{

  struct map *map = parse_map(map_p);
  SDL_Renderer* renderer = get_renderer();
  SDL_RenderClear(renderer);

  SDL_Event e;
  int quit = -1;
  int nbe = 10;
  struct player *player =  player_create(map->start_x, map->start_y, 3);
  struct enemy **enemies = enemy_create_all(map->spawns, nbe, 2);
  SDL_Rect rect_mdp = init_rect(800, 100, 200, 50);
  g_mdp = NULL;

  while (quit == -1)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.key.type == SDL_KEYDOWN)
      {
        move(e, renderer, map, player);
        if (e.key.keysym.sym == SDLK_ESCAPE)
          quit = 0;
      }
      else if (e.type == SDL_TEXTINPUT)
        move(e, renderer, map, player);
    }
    render_map(map, renderer);
    collision(enemies, player, nbe);
    move_all_enemies(enemies, nbe, map, renderer);
    collision(enemies, player, nbe);
    print_sprite(PLAYER, player->rect, renderer);
    if (g_mdp)
      render_text(g_mdp->mdp, pick_color(WHITE), renderer, rect_mdp);
    SDL_RenderPresent(renderer);
    if (player->life <= 0)
      quit = menu + 10;

    if (check_unlock(map))
      quit = 6;
    SDL_Delay(40);
  }
  free(player);
  return quit;
}

int level_choice(void)
{
  SDL_Renderer* renderer = get_renderer();
  SDL_RenderClear(renderer);
  int quit = 0;
  SDL_Event e;
  SDL_Rect sr_rect = init_rect(430,100,400,100);
  SDL_Rect past_rect = init_rect(430, 300, 400, 100);
  SDL_Rect vj_rect = init_rect(430, 500, 400, 100);
  SDL_Rect mid_rect = init_rect(430, 700, 400, 100);

  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(sr_rect))
        quit = 2;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(past_rect))
        quit = 3;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(vj_rect))
        quit = 4;
      if (e.type == SDL_MOUSEBUTTONDOWN && in_rect(mid_rect))
        quit = 5;
      if (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        quit = 127;
    }
    render_text("LabSR_SM14", pick_color(BLACK), renderer, sr_rect);
    render_text("Pasteur", pick_color(BLACK), renderer, past_rect);;
    render_text("Villejuif", pick_color(BLACK), renderer, vj_rect);
    render_text("MidLab", pick_color(BLACK), renderer, mid_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }
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
      menu = play("../../maps/LabSR_SM14.map", menu);
    else if (menu == 3)
      menu = play("../../maps/pasteur.map", menu);
    else if (menu == 4)
      menu = play("../../maps/VJ.map", menu);
    else if (menu == 5)
      menu = play("../../maps/midlab.map", menu);
    else if (menu == 6)
      menu = win();
    else 
      menu = die(menu);
  }
}

int main(void)
{
  srand(time(NULL));
  init();
  SDL_Window *screen = get_screen();
  game();

  free_sprites(get_renderer());
  SDL_DestroyRenderer(get_renderer());
  SDL_DestroyWindow(screen);
  SDL_Quit();
}
