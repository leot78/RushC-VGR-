#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "msdl.h"
#include "color.h"

TTF_Font* get_font(void)
{
  static TTF_Font *font = NULL;
  if (!font)
    font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 152);
  return font;
}

SDL_Texture *msg_texture(char *text, SDL_Color color, SDL_Renderer *renderer)
{
  TTF_Font *font = get_font();
  SDL_Surface *text_surface = TTF_RenderText_Solid(font, text,color);
  SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);
  return message;
}

void render_text(char *txt, SDL_Color color, SDL_Renderer *renderer, 
                  SDL_Rect rect)
{
  SDL_Texture* texture = msg_texture(txt, color, renderer);
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}
