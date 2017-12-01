#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <err.h>

#include "msdl.h"


#define FONT "/usr/share/fonts/TTF/LiberationMono-Regular.ttf"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* get_screen(void)
{
  static SDL_Window* screen = NULL;
  if (!screen)
    screen = SDL_CreateWindow("(Un)Lock Legacy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
      //color = {255, 0, 0, 0};
      color.r = 255;
      color.g = 0;
      color.b = 0;
      break;

    case WHITE:
      //color = {0, 0, 0, 0};
      color.r = 0;
      color.g = 0;
      color.b = 0;
      break;

    case GREEN:
      //color = {0, 255, 0, 0};
      color.r = 0;
      color.g = 255;
      color.b = 0;
      break;

    case BLUE:
      //color = {0, 0, 255, 0};
      color.r = 0;
      color.g = 0;
      color.b = 255;
      break;

    case GREY:
      //color = {127, 127, 127, 0};
      color.r = 127;
      color.g = 127;
      color.b = 127;
      break;
  }
  return color;
}

void move(SDL_Renderer *renderer, SDL_Rect *r, SDL_Event e)
{
  switch( e.key.keysym.sym )
  {
    case SDLK_UP:
      r->y -= 10;
      SDL_RenderFillRect( renderer, r );
      SDL_RenderPresent(renderer);
      break;

    case SDLK_DOWN:
      r->y += 10;
      SDL_RenderFillRect( renderer, r );

      SDL_RenderPresent(renderer);
      break;

    case SDLK_LEFT:
      r->x -= 10;
      SDL_RenderFillRect( renderer, r );

      SDL_RenderPresent(renderer);
      break;

    case SDLK_RIGHT:
      r->x += 10;
      SDL_RenderFillRect( renderer, r );

      SDL_RenderPresent(renderer);
      break;

    default:
      break;
  }
}

int main(void)
{
  init();

  TTF_Font *font = TTF_OpenFont(FONT, 172);
  if (!font)
    return -1;

  SDL_Window *screen = get_screen();

  SDL_Renderer* renderer = NULL;
  renderer =  SDL_CreateRenderer( screen, -1, SDL_RENDERER_ACCELERATED);
  SDL_Color color = {255, 255, 255, 0}; 

  int quit = 0;
  SDL_Event e;
  SDL_Texture *message = msg_texture(font, "(Un)Lock Legacy", color, renderer);
  SDL_Rect Message_rect = init_rect(100, 0, 400, 100);
  SDL_Rect r =  init_rect(50, 50, 50, 50);

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, message, NULL, &Message_rect);
  SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
  SDL_RenderFillRect( renderer, &r );

  SDL_RenderPresent(renderer);

  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
        quit = 1;
      else if( e.type == SDL_KEYDOWN )
      {
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );

        SDL_RenderCopy(renderer, message, NULL, &Message_rect);
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
        move(renderer, &r, e);
      }
    }
  }
  SDL_DestroyWindow(screen);

  SDL_Quit();
}
