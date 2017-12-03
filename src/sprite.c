#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "sprite.h"

SDL_Texture *get_ground(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../imgs/ground.png");
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
    loadedImage = IMG_Load("../imgs/wall.png");
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
    loadedImage = IMG_Load("../imgs/player.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_acu1(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../imgs/acu1.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_acu2(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../imgs/acu2.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_acu3(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../imgs/acu3.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

SDL_Texture *get_acu4(SDL_Renderer *renderer)
{

  SDL_Surface *loadedImage = NULL;
  static SDL_Texture *texture = NULL;
  if (!texture)
  {
    loadedImage = IMG_Load("../imgs/acu4.png");
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
    loadedImage = IMG_Load("../imgs/desklock.png");
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
    loadedImage = IMG_Load("../imgs/desk.png");
    texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
    SDL_FreeSurface(loadedImage);
  }
  return texture;
}

void free_sprites(SDL_Renderer *renderer)
{
  SDL_DestroyTexture(get_ground(renderer));
  SDL_DestroyTexture(get_wall(renderer));
  SDL_DestroyTexture(get_player(renderer));
  SDL_DestroyTexture(get_acu1(renderer));
  SDL_DestroyTexture(get_acu2(renderer));
  SDL_DestroyTexture(get_acu3(renderer));
  SDL_DestroyTexture(get_acu4(renderer));
  SDL_DestroyTexture(get_lock(renderer));
  SDL_DestroyTexture(get_pculock(renderer));
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

  if (sprite == ACU1)
    texture = get_acu1(renderer);

  if (sprite == ACU2)
    texture = get_acu2(renderer);

  if (sprite == ACU3)
    texture = get_acu3(renderer);

  if (sprite == ACU4)
    texture = get_acu4(renderer);

  if (sprite == PCLOCK)
    texture = get_lock(renderer);

  if (sprite == PCULOCK)
    texture = get_pculock(renderer);

  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
