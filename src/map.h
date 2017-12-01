#ifndef MAP_H
# define MAP_H

#include <stddef.h>

#include "object.h"

#define MAP_HEIGHT 30
#define MAP_WIDTH 40

struct map
{
  struct object ***objs;
  size_t width;
  size_t height;
};

struct map *map_init(size_t width, size_t height);
struct map *parse_map(const char *pathname);
void print_map(struct map *map);

#endif /* !MAP_H */
