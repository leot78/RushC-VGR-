#ifndef TEXT_H
# define TEXT_H

#include <SDL2/SDL.h>

void render_text(char *txt, SDL_Color color, SDL_Renderer *renderer, 
                  SDL_Rect rect);

#endif /* !TEXT_H */
