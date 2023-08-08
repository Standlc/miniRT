#include "minirt.h"

#define INTERVAL 5

void	set_cam_system(t_world *world)
{
	world->cam.system.z = world->cam.dir;
	world->cam.system.x = cross_product(&(t_vec){0, 1, 0}, &(world->cam.system.z));
	world->cam.system.y = cross_product(&(world->cam.system.z), &(world->cam.system.x));
}

void	print_system(t_system s)
{
	printf("x ");
	print_vector(s.x);
	printf("y ");
	print_vector(s.y);
	printf("z ");
	print_vector(s.z);
	printf("origin: ");
	print_vector(s.origin);
}

double  get_closest_intersection(double t1, double t2)
{
	if (t1 <= 0.0 && t2 <= 0.0)
		return (0.0);
	if (t1 <= 0.0)
		return (t2);
	if (t2 <= 0.0)
		return (t1);
	if (t1 < t2)
		return (t1);
	return (t2);
}

t_vec	to_world_coordinates(t_cam *cam, double x, double y)
{
	float	tan_cam_view_field;

	tan_cam_view_field = tan(cam->field_view / 2 * M_PI / 180);
	x = (2 * (x + 0.5) / WIDTH - 1) * tan_cam_view_field;
	y = (1 - 2 * (y + 0.5) / HEIGHT) * tan_cam_view_field * ((float)HEIGHT / WIDTH);
	return (system_transform(&(t_vec){x, y, 1.0}, &(cam->system)));
}

void	set_cam_ray(t_world *world, t_ray *cam_ray, int x, int y)
{
	t_vec	world_pixel;
	t_vec2	anti_aliasing;

	anti_aliasing.x = randf() * CAM_FUZZ - CAM_FUZZ / 2;
	anti_aliasing.y = randf() * CAM_FUZZ - CAM_FUZZ / 2;

	cam_ray->origin = world->cam.system.origin;
	world_pixel = to_world_coordinates(&(world->cam), x + anti_aliasing.x, y + anti_aliasing.y);
	cam_ray->dir = normalize(sub(world_pixel, cam_ray->origin));
}

t_vec	lerp(t_vec v1, t_vec v2, float t)
{
	v1.x = (1 - t) * v1.x + t * v2.x;
	v1.y = (1 - t) * v1.y + t * v2.y;
	v1.z = (1 - t) * v1.z + t * v2.z;
	return (v1);
}

int	intersect_objects(t_world *world, t_ray *ray, t_hit_info *hit)
{
	double	t;
	int		is_surface_hit;
	int		i;

	hit->t = INFINITY;
	is_surface_hit = 0;
	i = 0;
	while (i < world->nb_objects)
	{
		if (world->objects[i].intersect(ray, world->objects[i].shape, &t, &is_surface_hit)
			&& t < hit->t)
		{
			hit->t = t;
			hit->is_surface_hit = is_surface_hit;
			hit->obj = world->objects + i;
		}
		i++;
	}
	return (hit->t != INFINITY);
}

t_rgb	cast_ray(t_world *world, t_ray *ray, int is_specular_ray, int depth)
{
	t_hit_info	hit;

	if (depth > MAX_DEPTH + (is_specular_ray * MAX_DEPTH))
		return ((t_rgb){0.f, 0.f, 0.f});
	if (intersect_objects(world, ray, &hit))
	{
		// return (color_fade(hit.obj->color, min(30 / pow2(hit.t), 2) * 2));
		if (hit.obj->light_intensity && world->ambient < 1.0)
			return (color_fade(hit.obj->color, hit.obj->light_intensity * (1 - world->ambient)));
		hit.is_specular = is_specular_ray;
		return (shade_hitpoint(world, &hit, ray, depth));
	}
	if (world->ambient)
		return (ambient_light(&(world->ambient_light), ray, world->ambient));
	return ((t_rgb){0.f, 0.f, 0.f});
}

t_rgb	get_pixel_color(t_rt *rt, int x, int y)
{
	t_ray	cam_ray;
	t_rgb	pixel_color;

	set_cam_ray(&(rt->world), &cam_ray, x, y);
	pixel_color = cast_ray(&(rt->world), &cam_ray, 0, 1);

	rt->pixel_buff[y * WIDTH + x] = color_add(rt->pixel_buff[y * WIDTH + x], pixel_color);
	return (color_fade(rt->pixel_buff[y * WIDTH + x],
		1.f / ((rt->rendering_frame - 1) / INTERVAL + 1)));
}

int	render(t_rt *rt)
{
	int		y;
	int		x;

	// if ((rt->rendering_frame - 1) / INTERVAL + 1 > RPP)
	// 	return (0);
	if ((rt->rendering_frame - 1) / INTERVAL + 1 > 10)
		close_program(rt);
	y = 0;
	while (y < HEIGHT)
	{
		x = (rt->rendering_frame - 1) % INTERVAL;
		while (x < WIDTH)
		{
			put_pixel(rt, x, y, get_pixel_color(rt, x, y));
			x += INTERVAL;
		}
		y += 1;
	}
	loading_bar(RPP, (rt->rendering_frame - 1) / INTERVAL + 1);
	rt->rendering_frame += 1;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0);
	return (0);
}
