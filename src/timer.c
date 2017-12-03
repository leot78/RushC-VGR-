#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "timer.h"

struct timer g_time;

void init_time(void)
{
  g_time.ref = time(NULL);
}

char *get_time(void)
{
  time_t cur = time(NULL);
  if (!g_time.str)
    g_time.str = malloc(10);

  sprintf(g_time.str, "%ld", cur - g_time.ref);
  return g_time.str;
}

void free_timer(void)
{
  if (g_time.str)
    free(g_time.str);
}
