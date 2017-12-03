#include "enemy.h"

void enemy_delete_all(struct enemy**enemies, size_t len)
{
  for (size_t i = 0; i < len; i++)
    enemy_delete(enemies[i]);
}
