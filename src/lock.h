#ifndef LOCK_H
# define LOCK_H

#include "object.h"

int unlock_pc(struct object *pc);

char *generate_string(size_t len, int min, int max);

#endif /* !LOCK_H */
