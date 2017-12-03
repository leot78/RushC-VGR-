#ifndef SPRITE_H
# define SPRITE_H

enum sprite
{
  GROUND,
  SWALL,
  PLAYER,
  ACU,
  PCLOCK,
  PCULOCK
};


void print_sprite(enum sprite sprite, SDL_Rect rect, SDL_Renderer *renderer);

#endif /* !SPRITE_H */
