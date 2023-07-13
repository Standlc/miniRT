#include "minirt.h"

int intersect_cirlce(t_ray *ray, void *shape, double *t)
{
    t_circle    *circle;
    t_vec       hit_point;

    circle = (t_circle *)shape;
    if (!intersect_plane(ray, (void *)&(circle->plane), t))
        return (0);
    hit_point = get_ray_point(*ray, *t);
    if (vec_len(sub(hit_point, circle->plane.point)) <= circle->radius)
        return (1);
    *t = -1;
    return (0);
}