#ifndef COLOR_H
# define COLOR_H

#include <SDL2/SDL.h>

enum colors
{
  BLACK,
  RED,
  WHITE,
  GREEN,
  BLUE,
  GREY
};

SDL_Color pick_color(enum colors c);

#endif /* !COLOR_H */
