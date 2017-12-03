#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "timer.h"

time_t g_time;

void init_time(void)
{
  g_time = time(NULL);
}

time_t get_time(void)
{
  time_t cur = time(NULL);
  return 100 - cur - g_time;
}
