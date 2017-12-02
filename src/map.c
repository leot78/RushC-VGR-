#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "object.h"
#include "msdl.h"

struct map *map_init(size_t width, size_t height)
{
  struct map *map = malloc(sizeof(struct map));

  map->height = height;
  map->width = width;

  struct object ***objs = malloc(sizeof(struct object **) * width);

  for (size_t x = 0; x < width; ++x)
    objs[x] = malloc(sizeof(struct object *) * height);
  map->objs = objs;

  return map;
}

struct map *parse_map(const char *pathname)
{
  FILE *file = fopen(pathname, "r");
  if (!file)
    err(1, "cannot open file");

  char s[10];
  fgets(s, 10, file);
  size_t width = atoi(s);
  fgets(s, 10, file);
  size_t height = atoi(s);

  struct map *map = map_init(width, height);

  struct object ***objs = map->objs;
  for (size_t j = 0; j < height; ++j)
  {
    for (size_t i = 0; i < width; ++i)
    {
      int c = fgetc(file);
      if (c == '\n')
        c = fgetc(file);
      objs[i][j] = object_create(c, 0, i, j);
    }
  }

  return map;
}

void print_map(struct map *map)
{
  printf("width: %ld\n", map->width);
  printf("height: %ld\n", map->height);
  for (size_t j = 0; j < map->height; ++j)
  {
    for (size_t i = 0; i < map->width; ++i)
      print_obj(map->objs[i][j]);
    putchar('\n');
  }
}
