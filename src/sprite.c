#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "sprite.h"

SDL_Texture *get_ground(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/ground.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_wall(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/wall.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_player(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/player.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_acu(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/acu1.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_lock(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/desklock.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_pculock(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../../imgs/desk.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

void print_sprite(enum sprite sprite, SDL_Rect rect, SDL_Renderer *renderer)
{
  SDL_Texture *texture = NULL;
  if (sprite == GROUND)
    texture = get_ground(renderer);

  if (sprite == SWALL)
    texture = get_wall(renderer);

  if (sprite == PLAYER)
    texture = get_player(renderer);

  if (sprite == ACU)
    texture = get_acu(renderer);

  if (sprite == PCLOCK)
    texture = get_lock(renderer);

  if (sprite == PCULOCK)
    texture = get_pculock(renderer);


  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
