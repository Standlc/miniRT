#include "miniRT.h"

int	close_program(t_rt *rt);

void	print_vector(Vector v)
{
	printf("[%f, %f, %f],\n", v.x, v.y, v.z);
}

double  get_closest_intersection(double t1, double t2)
{
	if (t1 <= ZERO && t2 <= ZERO)
		return (-1);
	if (t1 <= ZERO)
		return (t2);
	if (t2 <= ZERO)
		return (t1);
	return (min(t1, t2));
}

Vector	to_world_coordinates(t_cam *cam, double x, double y)
{
	Vector	world_pixel;

	x = (2 * (x + 0.5) / WIDTH - 1) * tan(cam->field_view / 2 * M_PI / 180) / cam->aspect_ratio;
	y = (1 - 2 * (y + 0.5) / HEIGHT) * tan(cam->field_view / 2 * M_PI / 180);

	world_pixel.x = x * cam->space.x.x + y * cam->space.y.x + cam->space.z.x + cam->pos.x;
	world_pixel.y = x * cam->space.x.y + y * cam->space.y.y + cam->space.z.y + cam->pos.y;
	world_pixel.z = x * cam->space.x.z + y * cam->space.y.z + cam->space.z.z + cam->pos.z;
	return (world_pixel);
}

Ray	make_cam_ray(t_rt *rt, int x, int y)
{
	Ray		cam_ray;
	Vector	world_pixel;
	float	anti_aliasing_x;
	float	anti_aliasing_y;

	anti_aliasing_x = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;
	anti_aliasing_y = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;

	cam_ray.origin = rt->cam.pos;
	world_pixel = to_world_coordinates(&(rt->cam), x + anti_aliasing_x, y + anti_aliasing_y);
	cam_ray.dir = normalize(minus(world_pixel, cam_ray.origin));
	return (cam_ray);
}

Vector	random_dir()
{
	return (normalize((Vector){normal_randf(), normal_randf(), normal_randf()}));
}

Ray	cosine_hemisphere_ray(Vector *normal, Vector *origin)
{
	Ray		random_ray;

	random_ray.dir = normalize(add(random_dir(), *normal));
	random_ray.origin = *origin;
	return (random_ray);
}

Vector	lerp(Vector v1, Vector v2, float t)
{
	v1.x = (1 - t) * v1.x + t * v2.x;
	v1.y = (1 - t) * v1.y + t * v2.y;
	v1.z = (1 - t) * v1.z + t * v2.z;
	return (v1);
}

int	intersect_objects(t_rt *rt, Ray *ray, t_material *obj_hit, double *t)
{
	double	distance;
	int		i;

	*t = INFINITY;
	i = 0;
	while (i < rt->nb_objects)
	{
		if (rt->objects[i].intersect(ray, rt->objects + i, &distance) && distance < *t)
		{
			*t = distance;
			*obj_hit = rt->objects[i];
		}
		i++;
	}
	return (*t > 0 && *t != INFINITY);
}

Ray	fuzzy_shadow_ray(t_material *obj, Ray shadow_ray, Vector *hit_point, double *d_to_l)
{
	t_sphere	*sphere = (t_sphere *)(obj->shape);

	Vector	random_light_point = add(scale(random_dir(), sphere->radius), sphere->center);
	shadow_ray.origin = *hit_point;
	shadow_ray.dir = minus(random_light_point, *hit_point);
	*d_to_l = vector_len(shadow_ray.dir);
	shadow_ray.dir = normalize(shadow_ray.dir);
	return (shadow_ray);
}

int cast_shadow_ray(t_rt *rt, t_material *obj, Ray *shadow_ray, double distance_to_light)
{
	double  intersection_distance;
	int     i;

	i = 0;
	while (i < rt->nb_objects)
	{
		if (obj != rt->objects + i && 
			 rt->objects[i].intersect(shadow_ray, rt->objects + i, &intersection_distance) && 
			 intersection_distance < distance_to_light)
				return (0);
		i++;
	}
	return (1);
}

t_rgb	direct_light_sampling(t_rt *rt, Ray *shadow_ray, Vector *hit_point, Vector *normal)
{
	double		distance_to_light;
	t_material	*random_light;
	float		normal_shadow_dot;

	random_light = rt->lights[(int)roundf(randf() * (rt->nb_lights - 1))];
	*shadow_ray = fuzzy_shadow_ray(random_light, *shadow_ray, hit_point, &distance_to_light);
	normal_shadow_dot = relu(dot(*normal, shadow_ray->dir));
	if (!normal_shadow_dot)
		return ((t_rgb){0.f, 0.f, 0.f});

	if (cast_shadow_ray(rt, random_light, shadow_ray, distance_to_light))
	{
		return (color_fade(random_light->color, 
											min((random_light->light_entensity * 15) / pow(distance_to_light, 2), random_light->light_entensity)
											* normal_shadow_dot
											* rt->nb_lights
											));
	}
	return ((t_rgb){0.f, 0.f, 0.f});
}

t_rgb	cast_ray(t_rt *rt, Ray *ray, t_material **light_hit, int depth)
{
	double		intersection_distance;
	t_material	obj_hit;
	t_material	*next_ray_light_hit = NULL;
	Ray			shadow_ray;
	t_rgb		direct_light;

	if (depth > rt->opt.max_depth)
		return ((t_rgb){.0f, .0f, .0f});
	if (intersect_objects(rt, ray, &obj_hit, &intersection_distance))
	{
		return (obj_hit.color);
		if (obj_hit.light_entensity)
		{
			if (light_hit != NULL)
				*light_hit = &obj_hit;
			return (color_fade(obj_hit.color, obj_hit.light_entensity));
		}

		Vector  hit_point = get_line_point(*ray, intersection_distance);
		Vector  normal = obj_hit.normal(&obj_hit, &(ray->dir), &hit_point);
		Ray		random_ray = cosine_hemisphere_ray(&normal, &hit_point);

		int		is_specular = randf() < obj_hit.specular_prob;
		if (obj_hit.smoothness * is_specular)
		{
			Vector	reflection_vec = get_reflection(&(ray->dir), &normal);
			random_ray.dir = lerp(random_ray.dir, reflection_vec, obj_hit.smoothness * is_specular);
			return (color_fade(cast_ray(rt, &random_ray, NULL, depth + 1), 0.95));
		}

		t_rgb	hit_light = cast_ray(rt, &random_ray, &next_ray_light_hit, depth + 1);
		if (next_ray_light_hit == NULL)
		{
			direct_light = direct_light_sampling(rt, &shadow_ray, &hit_point, &normal);
			// return (color_mult(direct_light, obj_hit.color));
			hit_light = color_add(hit_light, direct_light);
		}
		return (color_mult(hit_light, obj_hit.color));
	}
	// return ((t_rgb){.0f, .0f, .0f});
	if (light_hit != NULL)
		*light_hit = rt->objects;
	return (ambient_light(ray));
}

int	render(t_rt *rt)
{
	Ray		cam_ray;
	int		y;
	int		x;

	if (rt->rendering_frame > rt->opt.rays_per_pixel)
	{
		// close_program(rt);
		return (0);
	}
	memset(rt->img.img_addr, 0, HEIGHT * WIDTH * (rt->img.bpp / 8));
	y = 0;
	while (y < rt->cam.screen_height)
	{
		x = 0;
		while (x < rt->cam.screen_width)
		{
			cam_ray = make_cam_ray(rt, x, y);
			rt->pixel_buff[y][x] = color_add(rt->pixel_buff[y][x], cast_ray(rt, &cam_ray, NULL, 1));
			put_pixel(rt, x, y, color_fade(rt->pixel_buff[y][x], 1.f / rt->rendering_frame));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0);
	loading_bar(rt->opt.rays_per_pixel, rt->rendering_frame);
	rt->rendering_frame += 1;
	return (0);
}

void	set_cam(t_rt *rt)
{
	rt->cam.space.z = normalize(minus(rt->cam.look_at, rt->cam.pos));
	rt->cam.space.x = cross_product(rt->space.y, rt->cam.space.z);
	rt->cam.space.y = cross_product(rt->cam.space.z, rt->cam.space.x);
	rt->cam.space.x = scale(rt->cam.space.x, -1);
}

void	clear_pixel_buff(t_rgb pixel_buff[HEIGHT][WIDTH])
{	
	memset(pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));
}

void	gather_lights(t_rt *rt)
{
	int	i;

	rt->nb_lights = 0;
	i = 0;
	while (i < rt->nb_objects)
	{
		if (rt->objects[i].light_entensity)
		{
			rt->lights[rt->nb_lights] = &(rt->objects[i]);
			rt->nb_lights += 1;
		}
		i++;
	}
}

int	main()
{
	t_rt      rt;
	rt.cam.screen_width = WIDTH;
	rt.cam.screen_height = HEIGHT;
	rt.cam.aspect_ratio = (float)HEIGHT / WIDTH;

	// tomato(&rt);
	balls_1(&rt);
	gather_lights(&rt);

	rt.opt.rays_per_pixel = 15;
	rt.opt.max_depth = 10;
	rt.opt.cam_ray_fuzz = 1.f;
	rt.opt.gamma = 1.f;

	rt.mlx = mlx_init();
	rt.win = mlx_new_window(rt.mlx, WIDTH, HEIGHT, "miniRT");
	rt.img.p = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	rt.img.img_addr = mlx_get_data_addr(rt.img.p, &rt.img.bpp,
			&rt.img.line_length, &rt.img.endian);
	rt.space.x = (Vector){1, 0, 0};
	rt.space.y = (Vector){0, 1, 0};
	rt.space.z = (Vector){0, 0, -1};

	clear_pixel_buff(rt.pixel_buff);
	rt.mouse.is_down = 0;
	rt.rendering_frame = 1;
	rt.cam.field_view = 40;
	// rt.cam.pos = (Vector){0, 0, 0};
	rt.cam.pos = (Vector){0, 3, 0};
	rt.cam.look_at = (Vector){0, 0, -15};
	set_cam(&rt);

	mlx_hook(rt.win, 2, 0, handle_key, &rt);
	mlx_hook(rt.win, ON_DESTROY, ON_DESTROY, close_program, &rt);

	mlx_hook(rt.win, 5, 0, handle_mouse_up, &rt);
	mlx_hook(rt.win, 6, 0, handle_mouse_move, &rt);
	mlx_mouse_hook(rt.win, handle_mouse, &rt);

	mlx_loop_hook(rt.mlx, render, &rt);

	mlx_loop(rt.mlx);
	return (0);
}
	// (2 + 3)/4 * (4/2)
		// float	fresnel = 0.5f + 0.5f * (1 - relu(dot(normal, scale(ray.dir, -1))));
		// fresnel = 1;
		// int		is_specular = randf() < obj_hit.specular_prob * fresnel;
// double  get_angle(Vector *v1, Vector *v2)
// {
// 	double  product;
// 	double  magnitude_v1;
// 	double  magnitude_v2;

// 	product = dot(*v1, *v2);
// 	magnitude_v1 = vector_len(*v1);
// 	magnitude_v2 = vector_len(*v2);
// 	return (acos(product / (magnitude_v1 * magnitude_v2)) * 180 / M_PI);
// }

// void	createCoordinateSystem(Vector normal, Vector *Nt, Vector *Nb)
// { 
//     if (fabs(normal.x) > fabs(normal.y))
//         *Nt = scale((Vector){normal.z, 0, -normal.x}, 1 / sqrtf(normal.x * normal.x + normal.z * normal.z));
//     else
//         *Nt = scale((Vector){0, -normal.z, normal.y}, 1 / sqrtf(normal.y * normal.y + normal.z * normal.z));
// 	*Nt = normalize(*Nt);
//     *Nb = cross_product(normal, *Nt);
// }

// Vector	get_cartesian_vector(float r1, float r2)
// {
//     float sinTheta = sqrtf(1 - r1 * r1);
//     float phi = 2 * M_PI * r2;
//     float x = sinTheta * cosf(phi);
//     float z = sinTheta * sinf(phi);
//     return (Vector){x, r1, z};
// }

// Vector	vector_to_world_coordinates(Vector v, Vector Nb, Vector Nt, Vector normal)
// {
// 	return (normalize((Vector){v.x * Nb.x + v.y * normal.x + v.z * Nt.x,
//         	v.x * Nb.y + v.y * normal.y + v.z * Nt.y,
//         	v.x * Nb.z + v.y * normal.z + v.z * Nt.z}));
// }

// Vector	get_random_hemisphere_vector(const Vector *normal)
// {
// 	Vector	vector;
// 	Vector	Nt;
// 	Vector	Nb;
// 	float	r1;
// 	float	r2;

// 	createCoordinateSystem(*normal, &Nt, &Nb);
// 	r1 = randf();
// 	r2 = randf();
// 	vector = get_cartesian_vector(r1, r2);
// 	vector = vector_to_world_coordinates(vector, Nb, Nt, *normal);
// 	return (vector);
// }

// double  cast_reflection_ray(t_rt *rt, Ray *reflection_ray, sphere **intersected_sphere)
// {
// 	double  temp_distance;
// 	double  intersection_distance;
// 	int i;

// 	intersection_distance = INFINITY;
// 	i = 0;
// 	while (i < rt->nb_objects)
// 	{
// 		if (intersect(*reflection_ray, rt->objects[i], &temp_distance) && temp_distance < intersection_distance)
// 		{
// 			intersection_distance = temp_distance;
// 			*intersected_sphere = &(rt->objects[i]);
// 		}
// 		i++;
// 	}
// 	return (intersection_distance);
// }

// Ray	make_shadow_ray(t_rt *rt, t_spot *light, Vector hit_point, double *distance)
// {
// 	Ray		shadow_ray;
// 	Vector	rand_f;

// 	rand_f.x = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	rand_f.y = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	rand_f.z = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	shadow_ray.dir = add(add(light->pos, '+', rand_f), '-', hit_point);
// 	*distance = vector_len(shadow_ray.dir);
// 	shadow_ray.dir = normalize(shadow_ray.dir);
// 	shadow_ray.origin = hit_point;
// 	return (shadow_ray);
// }


// t_rgb	cast_ray(t_rt *rt, Ray ray, int depth)
// {
// 	double	intersection_distance;
// 	Ray		shadow_ray;
// 	t_sphere	obj_hit;
// 	t_rgb	final_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	direct_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	specular_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	indirect_color = {0.0f, 0.0f, 0.0f};
// 	int	k = 0;

// 	if (depth > rt->opt.ray_max_depth)
// 		return ((t_rgb){0.0f, 0.0f, 0.0f});
// 	final_color = (t_rgb){0.0f, 0.0f, 0.0f};
// 	if (intersect_objects(rt, ray, &obj_hit, &intersection_distance))
// 	{
// 		Vector  hit_point = get_line_point(ray, intersection_distance);
// 		Vector  normal = add(hit_point, '-', obj_hit.center);
// 		normal = normalize(normal);
// 		k = 0;
// 		while (k < rt->nb_lights)
// 		{
// 			t_rgb	accum_direct_specular = {0.0f, 0.0f, 0.0f};
// 			Vector	reflection_vec = get_reflection(ray.dir, normal);
// 			// int	l = 0;
// 			// while (l < rt->opt.n_shadow_rays)
// 			// {
// 			// 	if (cast_shadow_ray(rt, &(rt->lights[k]), &shadow_ray, hit_point))
// 			// 	{
// 			// 		float	shadow_normal_dot = relu(dot(shadow_ray.dir, normal));
// 			// 		direct_color = color_fade(color_mult(rt->lights[k].color, obj_hit.color), shadow_normal_dot);

// 			// 		float	specular = pow(relu(dot(reflection_vec, shadow_ray.dir)), 5 + obj_hit.smoothness * 25) * shadow_normal_dot * (0.2f + obj_hit.smoothness * 0.4f);
// 			// 		specular_color = color_fade(rt->lights[k].color, specular);

// 			// 		accum_direct_specular = color_add(accum_direct_specular, direct_color);
// 			// 		accum_direct_specular = color_add(accum_direct_specular, specular_color);
// 			// 	}
// 			// 	l++;
// 			// }
// 			// accum_direct_specular = color_fade(accum_direct_specular, 1.0f / rt->opt.n_shadow_rays);
// 			// final_color = color_add(final_color, accum_direct_specular);

// 			// cast_shadow_ray(rt, &(rt->lights[k]), &shadow_ray, hit_point);
// 			Ray		random_ray = cosine_hemisphere_ray(&obj_hit, &normal, reflection_vec, hit_point);
// 			// float	reflection_intensity = relu(dot(reflection_vec, random_ray.dir));
// 			// float	diffuse_intensity = relu(dot(normal, shadow_ray.dir));
// 			// diffuse_intensity = 1;
// 			indirect_color = color_fade(color_mult(cast_ray(rt, random_ray, depth + 1), obj_hit.color), 1);
// 			final_color = color_add(final_color, indirect_color);
// 			k++;
// 		}
// 		return (final_color);
// 	}
// 	return ((t_rgb){0.5f, 0.7f, 1.0f});
// }


// int	render(t_rt *rt)
// {
// 	Ray		cam_ray;
// 	t_rgb	pixel_color;
// 	int		i;
// 	int		j;
// 	int		k;

// 	bzero(rt->img.img_addr, HEIGHT * WIDTH * (rt->img.bpp / 8));
// 	i = 0;
// 	while (i < rt->cam.screen_height)
// 	{
// 		j = 0;
// 		while (j < rt->cam.screen_width)
// 		{
// 			pixel_color = (t_rgb){0.0f, 0.0f, 0.0f};
// 			k = 0;
// 			while (k < rt->opt.rays_per_pixel)
// 			{
// 				cam_ray = make_cam_ray(rt, j, i);
// 				pixel_color = color_add(pixel_color, cast_ray(rt, cam_ray, 1));
// 				k++;
// 			}
// 			put_pixel(rt, j, i, color_fade(pixel_color, 1.0f/rt->opt.rays_per_pixel));
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0);
// 	return (0);
// }


// int k = 0;
// while (k < rt->nb_lights)
// {
// 	if (cast_shadow_ray(rt, &(rt->lights[k]), shadow_ray, hit_point))
// 	{
// 		double	distance_to_light_2 = pow(vector_len(add(rt->lights[k].pos, hit_point, '-')), 2);
// 		double	shadow_normal_dot = relu(dot(shadow_ray.dir, normal));

// 		t_rgb	diffuse_color = color_mult(rt->lights[k].color, obj_hit.color);
// 		diffuse_color = color_fade(diffuse_color, 100 / distance_to_light_2 * shadow_normal_dot);

// 		Vector	reflection_vec = get_reflection(ray.dir, normal);
// 		float	specular = pow(relu(dot(reflection_vec, shadow_ray.dir)), 10) * shadow_normal_dot;
// 		t_rgb	specular_color = color_fade(rt->lights[k].color, 100 / distance_to_light_2 * specular * 0.8);

// 		color = color_add(color, diffuse_color);
// 		color = color_add(color, specular_color);
// 	}
// 	k++;
// }
// if (depth < rt->ray_max_depth)
// {
// 	int	indirect_color = 0;
// 	int	max_depth = 0;
// 	Ray	indirect_ray;
// 	indirect_ray.origin = hit_point;
// 	while (max_depth < 128)
// 	{
// 		int	curr_indirect_color = 0;
// 		indirect_ray.dir = get_random_hemisphere_vector(&normal);
// 		cast_ray(rt, indirect_ray, &curr_indirect_color, depth + 1);
// 		if (curr_indirect_color)
// 		{
// 			curr_indirect_color = get_light_color(curr_indirect_color, obj_hit.color);
// 			curr_indirect_color = fade_color(curr_indirect_color, dot(normal, indirect_ray.dir) * (1 / 128.0));
// 			indirect_color = blend_colors(indirect_color, curr_indirect_color);
// 		}
// 		max_depth++;
// 	}
// 	*color = blend_colors(*color, indirect_color);
// }
// cast_reflections(rt, &cam_ray.dir, &hit_point, &obj_hit, &color, 10);



// void    cast_reflections(t_rt *rt, Vector *ray_dir, Vector *hit_point, sphere *intersected_sphere, int *color, int i)
// {
// 	Vector  normal = add(*hit_point, intersected_sphere->center, '-');
// 	normal = normalize(normal);
// 	Ray     reflection_ray;
// 	sphere  *reflection_intersected_sphere;

// 	if (!i)
// 		return ;
// 	reflection_ray.dir = get_reflection(*ray_dir, normal);
// 	reflection_ray.dir = normalize(reflection_ray.dir);
// 	reflection_ray.origin = *hit_point;
// 	double  reflection_t = cast_reflection_ray(rt, &reflection_ray, &reflection_intersected_sphere);
// 	if (reflection_t > 0 && reflection_t < INFINITY)
// 	{
// 		Vector  reflection_int_point = get_line_point(reflection_ray, reflection_t);
// 		if (cast_shadow_ray(rt, &(rt->lights[0]), reflection_int_point))
// 		{
// 			Vector  shadow_ray = add(rt->lights[0].pos, reflection_int_point, '-');
// 			shadow_ray = normalize(shadow_ray);
// 			Vector  normal = add(reflection_int_point, reflection_intersected_sphere->center, '-');
// 			normal = normalize(normal);
// 			int reflected_color = fade_color(reflection_intersected_sphere->color, dot(shadow_ray, normal) * intersected_sphere->reflectivity);
// 			// *color |= reflected_color;
// 			*color = blend_colors(*color, reflected_color);
// 			cast_reflections(rt, &reflection_ray.dir, &reflection_int_point, reflection_intersected_sphere, color, i - 1);
// 		}
// 	}
// }
