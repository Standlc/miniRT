#include "minirt.h"

// t_vec	rect_normal(void *shape, t_vec *ray_dir, t_vec *hit_point)
// {
// 	t_vec	normal;

// 	(void)hit_point;
// 	normal = ((t_rect *)shape)->normal;
// 	if (ray_dir && dot(normal, *ray_dir) > 0)
// 		return (scale(normal, -1));
// 	return (normal);
// }

// int	intersect_rect(t_ray *ray, void *shape, double *t)
// {
// 	t_rect	*rect;
// 	t_vec	center_to_intersection;
// 	t_plane	rect_plane;
// 	t_vec	projected;
// 	double	projected_len;

// 	rect = (t_rect*)shape;
// 	rect_plane = (t_plane){rect->center, rect->normal};
// 	if (!intersect_plane(ray, (void *)&rect_plane, t))
// 		return (0);

// 	center_to_intersection = sub(get_ray_point(*ray, *t), rect->center);

// 	projected = project(center_to_intersection, rect->side_a);
// 	projected_len = vec_len(projected);
// 	if (projected_len > vec_len(rect->side_a) / 2)
// 		return (0);

// 	projected = project(center_to_intersection, rect->side_b);
// 	projected_len = vec_len(projected);
// 	return (projected_len < vec_len(rect->side_b) / 2);
// }

// t_vec	sample_rect(void *shape, t_ray *normal)
// {
// 	t_rect	*rect;
// 	t_vec	random_dir;

// 	(void)normal;
// 	rect = (t_rect *)shape;
// 	random_dir = add(scale(rect->side_a, randf() - 0.5), scale(rect->side_b, randf() - 0.5));
// 	// return (rect->center);
// 	return (add(rect->center, random_dir));
// }
