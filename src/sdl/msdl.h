#ifndef MSDL_H
# define MSDL_H

#include <SDL2/SDL.h>



#define FONT "/usr/share/fonts/TTF/LiberationMono-Regular.ttf"

#define SCREEN_WIDTH 640;
#define SCREEN_HEIGHT 480;

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
SDL_Rect init_rect(int x, int y, int w, int h);

#endif /* !MSDL_H */
