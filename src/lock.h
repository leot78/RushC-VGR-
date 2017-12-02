#ifndef LOCK_H
# define LOCK_H

#include "object.h"

extern char buff[127];

char *unlock_pc(struct object *pc);
int unlock_pc_checker();

char *generate_string(size_t len, int min, int max);

#endif /* !LOCK_H */
