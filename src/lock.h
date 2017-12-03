#ifndef LOCK_H
# define LOCK_H

#include "object.h"


struct mdp
{
  char *mdp;
  char input[127];
};

extern struct mdp *g_mdp;

int unlock_pc_checker(char *s, char *mdp, int size_mdp);
void unlock_pc(struct object *obj);
char *start_unlock(int size);

char *generate_string(size_t len, int min, int max);

#endif /* !LOCK_H */
