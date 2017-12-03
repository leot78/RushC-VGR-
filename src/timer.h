#ifndef TIMER_H
# define TIMER_H

#include <time.h>

struct timer
{
  time_t ref;
  char *str;
};

char *get_time(void);
void init_time(void);
void free_timer(void);

#endif /* !TIMER_H */
