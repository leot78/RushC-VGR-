#ifndef VECTOR2_H
# define VECTOR2_H

struct vect2
{
  int x;
  int y;
};

struct vect2 *vect2_create(int x, int y);
void vect2_delete(struct vect2 *v);

#endif /* !VECTOR2_H */
