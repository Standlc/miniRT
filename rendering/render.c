#include "minirt.h"

void	set_cam_system(t_rt *rt)
{
	rt->cam.system.z = rt->cam.dir;
	rt->cam.system.x = cross_product(rt->system.y, rt->cam.system.z);
	rt->cam.system.y = cross_product(rt->cam.system.z, rt->cam.system.x);
}

void	print_vector(t_vec v)
{
	printf("[%f, %f, %f],\n", v.x, v.y, v.z);
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
	if (t1 <= ZERO && t2 <= ZERO)
		return (-1.0);
	if (t1 <= ZERO)
		return (t2);
	if (t2 <= ZERO)
		return (t1);
	return (min(t1, t2));
}

t_vec	to_world_coordinates(t_cam *cam, double x, double y)
{
	float	tan_cam_view_field;

	tan_cam_view_field = tan(cam->field_view / 2 * M_PI / 180);
	x = (2 * (x + 0.5) / WIDTH - 1) * tan_cam_view_field;
	y = (1 - 2 * (y + 0.5) / HEIGHT) * tan_cam_view_field * cam->aspect_ratio;

	return (system_transform((t_vec){x, y, 1.0}, cam->system));
}

void	set_cam_ray(t_rt *rt, t_ray *cam_ray, int x, int y)
{
	t_vec	world_pixel;
	t_vec2	anti_aliasing;

	anti_aliasing.x = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;
	anti_aliasing.y = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;

	cam_ray->origin = rt->cam.system.origin;
	world_pixel = to_world_coordinates(&(rt->cam), x + anti_aliasing.x, y + anti_aliasing.y);
	cam_ray->dir = normalize(sub(world_pixel, cam_ray->origin));
}

t_vec	lerp(t_vec v1, t_vec v2, float t)
{
	v1.x = (1 - t) * v1.x + t * v2.x;
	v1.y = (1 - t) * v1.y + t * v2.y;
	v1.z = (1 - t) * v1.z + t * v2.z;
	return (v1);
}

int	intersect_objects(t_rt *rt, t_ray *ray, t_hit_info *hit)
{
	double	t_curr;
	int		is_surface_hit;
	int		i;

	hit->t = INFINITY;
	is_surface_hit = 0;
	i = 0;
	while (i < rt->nb_objects)
	{
		if (rt->objects[i].intersect(ray, rt->objects[i].shape, &t_curr, &is_surface_hit)
			&& t_curr < hit->t)
		{
			hit->t = t_curr;
			hit->is_surface_hit = is_surface_hit;
			hit->obj = rt->objects[i];
		}
		i++;
	}
	return (hit->t != INFINITY);
}

t_rgb	cast_ray(t_rt *rt, t_ray *ray, int is_specular_ray, int depth)
{
	t_hit_info	hit;

	if (depth > rt->opt.max_depth + (is_specular_ray * rt->opt.max_depth))
		return ((t_rgb){0.f, 0.f, 0.f});
	if (intersect_objects(rt, ray, &hit))
	{
		// return (color_fade(hit.obj.color, 10 / pow(hit.t, 2)));

		if (hit.obj.light_intensity && rt->opt.ambient < 1.0)
			return (color_fade(hit.obj.color, hit.obj.light_intensity * 5 * (1 - rt->opt.ambient)));
		hit.is_specular = is_specular_ray;
		return (shade_hitpoint(rt, &hit, ray, depth));
	}
	if (rt->opt.ambient)
		return (ambient_light(rt->opt.ambient_light, ray, rt->opt.ambient));
	return ((t_rgb){0.f, 0.f, 0.f});
}

t_rgb	get_pixel_color(t_rt *rt, int x, int y)
{
	t_ray	cam_ray;
	t_rgb	pixel_color;

	set_cam_ray(rt, &cam_ray, x, y);
	pixel_color = cast_ray(rt, &cam_ray, 0, 1);

	if (rt->opt.pixel_rendered_interval > 1)
		pixel_color = color_fade(pixel_color, 2);

	rt->pixel_buff[y * WIDTH + x] = color_add(rt->pixel_buff[y * WIDTH + x], pixel_color);
	return (color_fade(rt->pixel_buff[y * WIDTH + x], 1.f / rt->rendering_frame));
}

int	render(t_rt *rt)
{
	int		y;
	int		x;

	if (rt->rendering_frame > rt->opt.rpp)
		return (0);
	ft_memset(rt->img.img_addr, 0, HEIGHT * WIDTH * (rt->img.bpp / 8));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(rt, x, y, get_pixel_color(rt, x, y));
			x += rt->opt.pixel_rendered_interval;
		}
		y += 1;
	}
	if (rt->opt.pixel_rendered_interval == 1)
		loading_bar(rt->opt.rpp, rt->rendering_frame);
	rt->rendering_frame += 1;
	return (mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0), 0);
}
