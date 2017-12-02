#include <SDL2/SDL.h>

#include "color.h"

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


