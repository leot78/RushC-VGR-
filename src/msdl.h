#ifndef MSDL_H
# define MSDL_H

#include <SDL2/SDL.h>



#define FONT "/usr/share/fonts/TTF/LiberationMono-Regular.ttf"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

SDL_Rect init_rect(int x, int y, int w, int h);

#endif /* !MSDL_H */
