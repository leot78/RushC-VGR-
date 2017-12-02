#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
** Generate a string with random char between int and max
** (Adviced min = 97, max = 123)
*/
char *generate_string(size_t len, int min, int max)
{
  int offset = max - min;
  char *res = malloc(sizeof(char) * len);
  for (size_t i = 0; i < len; i++)
    res[i] = (rand() % offset) + min;
  return res;
}
