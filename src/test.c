#include <stdio.h>

#include "object.h"
#include "map.h"

int main(int argc, char **argv)
{
  if (argc != 2)
    return 0;

  struct map *map = parse_map(argv[1]);
  print_map(map);
}
