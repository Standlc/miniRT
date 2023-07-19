#include "minirt.h"

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

	return (system_transform((t_vec){x, y, -1.0}, cam->system));
}

t_ray	make_cam_ray(t_rt *rt, int x, int y)
{
	t_ray	cam_ray;
	t_vec	world_pixel;
	t_point	anti_aliasing;

	anti_aliasing.x = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;
	anti_aliasing.y = randf() * rt->opt.cam_ray_fuzz - rt->opt.cam_ray_fuzz / 2;

	cam_ray.origin = rt->cam.system.origin;
	world_pixel = to_world_coordinates(&(rt->cam), x + anti_aliasing.x, y + anti_aliasing.y);
	cam_ray.dir = normalize(sub(world_pixel, cam_ray.origin));
	return (cam_ray);
}

t_vec	lerp(t_vec v1, t_vec v2, float t)
{
	v1.x = (1 - t) * v1.x + t * v2.x;
	v1.y = (1 - t) * v1.y + t * v2.y;
	v1.z = (1 - t) * v1.z + t * v2.z;
	return (v1);
}

int	intersect_objects(t_rt *rt, t_ray *ray, t_hit_info *hit, double *t)
{
	double	distance;
	int		surface_hit;
	int		i;

	*t = INFINITY;
	i = 0;
	while (i < rt->nb_objects)
	{
		if (rt->objects[i].intersect(ray, rt->objects[i].shape, &distance, &surface_hit)
			&& distance < *t)
		{
			*t = distance;
			hit->surface_hit = surface_hit;
			hit->obj = rt->objects[i];
		}
		i++;
	}
	return (*t != INFINITY);
}

t_rgb	cast_ray(t_rt *rt, t_ray *ray, int is_specular_ray, int depth)
{
	t_hit_info	hit;

	if (depth > rt->opt.max_depth + (is_specular_ray * rt->opt.max_depth))
		return ((t_rgb){0.f, 0.f, 0.f});
	if (intersect_objects(rt, ray, &hit, &hit.t))
	{
		// return (color_fade(hit.obj.color, 10 / pow(hit.t, 2)));

		if (hit.obj.light_intensity && rt->opt.ambient < .5)
			return (color_fade(hit.obj.color, hit.obj.light_intensity * (1 - rt->opt.ambient)));
		hit.is_specular = is_specular_ray;
		hit.normal.origin = get_ray_point(*ray, hit.t);
		hit.normal.dir = hit.obj.normal(&(ray->dir), hit.obj.shape, &hit.normal.origin, hit.surface_hit);
		return (shade_hitpoint(rt, &hit, ray, depth));
	}
	if (rt->opt.ambient)
		return (ambient_light(rt->opt.ambient_light, ray, rt->opt.ambient));
	return ((t_rgb){0.f, 0.f, 0.f});
}

int	render(t_rt *rt)
{
	t_ray	cam_ray;
	t_rgb	pixel_color;
	int		y;
	int		x;

	// if (rt->rendering_frame > rt->opt.rpp)
	// 	return (0);
	// if (rt->rendering_frame > 10)
	// {
	// 	close_program(rt);
	// }
	ft_memset(rt->img.img_addr, 0, HEIGHT * WIDTH * (rt->img.bpp / 8));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cam_ray = make_cam_ray(rt, x, y);
			pixel_color = cast_ray(rt, &cam_ray, 0, 1);

			if (rt->opt.pixel_rendered_interval > 1)
				pixel_color = color_fade(pixel_color, rt->opt.pixel_rendered_interval);

			rt->pixel_buff[y * WIDTH + x] = color_add(rt->pixel_buff[y * WIDTH + x], pixel_color);
			put_pixel(rt, x, y, color_fade(rt->pixel_buff[y * WIDTH + x], 1.f / rt->rendering_frame));
			x += rt->opt.pixel_rendered_interval;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img.p, 0, 0);
	if (rt->opt.pixel_rendered_interval == 1)
		loading_bar(rt->opt.rpp, rt->rendering_frame);
	rt->rendering_frame += 1;
	return (0);
}

void	set_cam_system(t_rt *rt)
{
	rt->cam.system.z = normalize(sub(rt->cam.look_at, rt->cam.system.origin));
	rt->cam.system.x = cross_product(rt->cam.system.z, rt->system.y);
	rt->cam.system.y = cross_product(rt->cam.system.x, rt->cam.system.z);
}

void	gather_lights(t_rt *rt)
{
	int	i;

	rt->nb_lights = 0;
	i = 0;
	while (i < rt->nb_objects)
	{
		if (rt->objects[i].light_intensity)
		{
			rt->lights[rt->nb_lights] = &(rt->objects[i]);
			rt->nb_lights += 1;
		}
		i++;
	}
}

void	other_shapes(t_rt *rt);

void	set_null(t_rt *rt)
{
	rt->mlx = NULL;
	rt->win = NULL;
	rt->objects = NULL;
	rt->lights = NULL;
	rt->pixel_buff = NULL;
	rt->img.p = NULL;
	rt->img.img_addr = NULL;
}

int	main(int argc, char **argv)
{
	t_rt	rt;
	rt.cam.aspect_ratio = (float)HEIGHT / WIDTH;

	//tomato(&rt);
	// balls_1(&rt);
	// kernel(&rt);
	//other_shapes(&rt);
	//gather_lights(&rt);

	// rt.opt.gamma = 1.f;
	rt.opt.rpp = RPP;
	rt.opt.max_depth = MAX_DEPTH;
	rt.opt.cam_ray_fuzz = 1.f;
	rt.opt.pixel_rendered_interval = 1;

	set_null(&rt);
	parsing(argc, argv, &rt);
	rt.mlx = mlx_init();
	if (!rt.mlx)
		(error_allocation(), free_elements(&rt), exit(1));
	rt.win = mlx_new_window(rt.mlx, WIDTH, HEIGHT, "miniRT");
	rt.img.p = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	if (!rt.win || !rt.img.p)
		(error_allocation(), free_elements(&rt), exit(1));
	rt.img.img_addr = mlx_get_data_addr(rt.img.p, &rt.img.bpp,
			&rt.img.line_length, &rt.img.endian);
	if (!rt.img.img_addr)
		(error_allocation(), free_elements(&rt), exit(1));
	rt.system.x = (t_vec){1, 0, 0};
	rt.system.y = (t_vec){0, 1, 0};
	rt.system.z = (t_vec){0, 0, -1};
	rt.system.origin = (t_vec){0, 0, 0};

	rt.mouse.is_down = 0;
	rt.rendering_frame = 1;
	set_cam_system(&rt);

	
	rt.pixel_buff = malloc(sizeof(t_rgb) * HEIGHT * WIDTH);
	if (!rt.pixel_buff)
		(error_allocation(), free_elements(&rt), exit(1));
	ft_memset(rt.pixel_buff, 0, HEIGHT * WIDTH * sizeof(t_rgb));

	mlx_hook(rt.win, 2, 0, handle_key, &rt);
	mlx_hook(rt.win, ON_DESTROY, 0, close_program, &rt);
	mlx_hook(rt.win, 5, 0, handle_mouse_up, &rt);
	mlx_hook(rt.win, 6, 0, handle_mouse_move, &rt);
	mlx_mouse_hook(rt.win, handle_mouse, &rt);
	
	mlx_loop_hook(rt.mlx, render, &rt);

	mlx_loop(rt.mlx);
	close_program(&rt);
	return (0);
}



// t_rgb	cast_ray(t_rt *rt, t_ray *ray, t_material **light_hit, int depth)
// {
// 	double		t_distance;
// 	t_material	obj_hit;
// 	t_material	*next_ray_light_hit = NULL;
// 	t_rgb		direct_light;
// 	t_rgb		color;

// 	color = (t_rgb){.0f, .0f, .0f};
// 	if (depth > rt->opt.max_depth)
// 		return (color);
// 	if (intersect_objects(rt, ray, &obj_hit, &t_distance))
// 	{
// 		if (obj_hit.light_intensity)
// 		{
// 			if (light_hit != NULL)
// 				*light_hit = &obj_hit;
// 			return (color_fade(obj_hit.color, obj_hit.light_intensity));
// 		}

// 		t_vec	hit_point = get_ray_point(*ray, t_distance);
// 		t_vec	normal = obj_hit.normal(obj_hit.shape, &(ray->dir), &hit_point);
// 		t_ray		random_ray = cosine_hemisphere_ray(&normal, &hit_point);

// 		if (obj_hit.smoothness * (randf() < obj_hit.specular_prob))
// 		{
// 			t_vec	reflection_vec = get_reflection(&(ray->dir), &normal);
// 			random_ray.dir = lerp(random_ray.dir, reflection_vec, obj_hit.smoothness);
// 			return (color_fade(cast_ray(rt, &random_ray, NULL, depth + 1), 0.95f));
// 		}

// 		color = cast_ray(rt, &random_ray, &next_ray_light_hit, depth + 1);
// 		if (next_ray_light_hit == NULL)
// 			color = color_fade(color, 0.7);

// 		if (
// 			next_ray_light_hit == NULL && 
// 			rt->nb_lights)
// 		{
// 			direct_light = direct_light_sampling(rt, &hit_point, &normal);
// 			// return (color_mult(direct_light, obj_hit.color));
// 			color = color_add(color, direct_light);
// 		}
// 		return (color_mult(color, obj_hit.color));
// 	}
// 	return (color);
// 	if (light_hit != NULL)
// 		*light_hit = rt->objects;
// 	return (ambient_light(ray));
// }

		// if (obj_hit.specular_prob)
		// {
		// 	t_vec	reflection_vec = get_reflection(&(ray->dir), &normal);
		// 	t_ray		reflection_ray;
		// 	reflection_ray.dir = lerp(random_ray.dir, reflection_vec, obj_hit.smoothness);
		// 	reflection_ray.origin = hit_point;
		// 	light = color_fade(cast_ray(rt, &reflection_ray, 1, depth + 1), 0.95f * obj_hit.specular_prob);
		// 	if (obj_hit.specular_prob == 1.f)
		// 		return (light);
		// }

		// t_rgb indirect_light = cast_ray(rt, &random_ray, 0, depth + 1);
		// if (!is_specular_ray && depth > 1)
		// 	indirect_light = color_fade(indirect_light, 0.7);

		// if (rt->nb_lights)
		// {
		// 	direct_light = direct_light_sampling(rt, &hit_point, &normal);
		// 	indirect_light = color_add(indirect_light, direct_light);
		// }

		// indirect_light = color_fade(indirect_light, 1 - obj_hit.specular_prob);
		// indirect_light = color_mult(indirect_light, obj_hit.color);
		// indirect_light = color_add(indirect_light, light);
		// indirect_light = clamp(indirect_light, 1.f);
		// return (indirect_light);


	// (2 + 3)/4 * (4/2)
		// float	fresnel = 0.5f + 0.5f * (1 - relu(dot(normal, scale(ray.dir, -1))));
		// fresnel = 1;
		// int		is_specular = randf() < obj_hit.specular_prob * fresnel;

// void	createCoordinateSystem(t_vec normal, t_vec *Nt, t_vec *Nb)
// { 
//     if (fabs(normal.x) > fabs(normal.y))
//         *Nt = scale((t_vec){normal.z, 0, -normal.x}, 1 / sqrtf(normal.x * normal.x + normal.z * normal.z));
//     else
//         *Nt = scale((t_vec){0, -normal.z, normal.y}, 1 / sqrtf(normal.y * normal.y + normal.z * normal.z));
// 	*Nt = normalize(*Nt);
//     *Nb = cross_product(normal, *Nt);
// }

// t_vec	get_cartesian_vector(float r1, float r2)
// {
//     float sinTheta = sqrtf(1 - r1 * r1);
//     float phi = 2 * M_PI * r2;
//     float x = sinTheta * cosf(phi);
//     float z = sinTheta * sinf(phi);
//     return (t_vec){x, r1, z};
// }

// t_vec	vector_to_world_coordinates(t_vec v, t_vec Nb, t_vec Nt, t_vec normal)
// {
// 	return (normalize((t_vec){v.x * Nb.x + v.y * normal.x + v.z * Nt.x,
//         	v.x * Nb.y + v.y * normal.y + v.z * Nt.y,
//         	v.x * Nb.z + v.y * normal.z + v.z * Nt.z}));
// }

// t_vec	get_random_hemisphere_vector(const t_vec *normal)
// {
// 	t_vec	vector;
// 	t_vec	Nt;
// 	t_vec	Nb;
// 	float	r1;
// 	float	r2;

// 	createCoordinateSystem(*normal, &Nt, &Nb);
// 	r1 = randf();
// 	r2 = randf();
// 	vector = get_cartesian_vector(r1, r2);
// 	vector = vector_to_world_coordinates(vector, Nb, Nt, *normal);
// 	return (vector);
// }

// double  cast_reflection_ray(t_rt *rt, t_ray *reflection_ray, sphere **intersected_sphere)
// {
// 	double  temp_distance;
// 	double  t_distance;
// 	int i;

// 	t_distance = INFINITY;
// 	i = 0;
// 	while (i < rt->nb_objects)
// 	{
// 		if (intersect(*reflection_ray, rt->objects[i], &temp_distance) && temp_distance < t_distance)
// 		{
// 			t_distance = temp_distance;
// 			*intersected_sphere = &(rt->objects[i]);
// 		}
// 		i++;
// 	}
// 	return (t_distance);
// }

// t_ray	make_shadow_ray(t_rt *rt, t_spot *light, t_vec hit_point, double *distance)
// {
// 	t_ray		shadow_ray;
// 	t_vec	rand_f;

// 	rand_f.x = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	rand_f.y = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	rand_f.z = randf() * rt->opt.shadow_ray_offset - rt->opt.shadow_ray_offset / 2;
// 	shadow_ray.dir = add(add(light->pos, '+', rand_f), '-', hit_point);
// 	*distance = vec_len(shadow_ray.dir);
// 	shadow_ray.dir = normalize(shadow_ray.dir);
// 	shadow_ray.origin = hit_point;
// 	return (shadow_ray);
// }


// t_rgb	cast_ray(t_rt *rt, t_ray ray, int depth)
// {
// 	double	t_distance;
// 	t_ray		shadow_ray;
// 	t_sphere	obj_hit;
// 	t_rgb	final_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	direct_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	specular_color = {0.0f, 0.0f, 0.0f};
// 	t_rgb	indirect_color = {0.0f, 0.0f, 0.0f};
// 	int	k = 0;

// 	if (depth > rt->opt.ray_max_depth)
// 		return ((t_rgb){0.0f, 0.0f, 0.0f});
// 	final_color = (t_rgb){0.0f, 0.0f, 0.0f};
// 	if (intersect_objects(rt, ray, &obj_hit, &t_distance))
// 	{
// 		t_vec  hit_point = get_ray_point(ray, t_distance);
// 		t_vec  normal = add(hit_point, '-', obj_hit.center);
// 		normal = normalize(normal);
// 		k = 0;
// 		while (k < rt->nb_lights)
// 		{
// 			t_rgb	accum_direct_specular = {0.0f, 0.0f, 0.0f};
// 			t_vec	reflection_vec = get_reflection(ray.dir, normal);
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
// 			t_ray		random_ray = cosine_hemisphere_ray(&obj_hit, &normal, reflection_vec, hit_point);
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
// 	t_ray		cam_ray;
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
// 		double	distance_to_light_2 = pow(vec_len(add(rt->lights[k].pos, hit_point, '-')), 2);
// 		double	shadow_normal_dot = relu(dot(shadow_ray.dir, normal));

// 		t_rgb	diffuse_color = color_mult(rt->lights[k].color, obj_hit.color);
// 		diffuse_color = color_fade(diffuse_color, 100 / distance_to_light_2 * shadow_normal_dot);

// 		t_vec	reflection_vec = get_reflection(ray.dir, normal);
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
// 	t_ray	indirect_ray;
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



// void    cast_reflections(t_rt *rt, t_vec *ray_dir, t_vec *hit_point, sphere *intersected_sphere, int *color, int i)
// {
// 	t_vec  normal = add(*hit_point, intersected_sphere->center, '-');
// 	normal = normalize(normal);
// 	t_ray     reflection_ray;
// 	sphere  *reflection_intersected_sphere;

// 	if (!i)
// 		return ;
// 	reflection_ray.dir = get_reflection(*ray_dir, normal);
// 	reflection_ray.dir = normalize(reflection_ray.dir);
// 	reflection_ray.origin = *hit_point;
// 	double  reflection_t = cast_reflection_ray(rt, &reflection_ray, &reflection_intersected_sphere);
// 	if (reflection_t > 0 && reflection_t < INFINITY)
// 	{
// 		t_vec  reflection_int_point = get_ray_point(reflection_ray, reflection_t);
// 		if (cast_shadow_ray(rt, &(rt->lights[0]), reflection_int_point))
// 		{
// 			t_vec  shadow_ray = add(rt->lights[0].pos, reflection_int_point, '-');
// 			shadow_ray = normalize(shadow_ray);
// 			t_vec  normal = add(reflection_int_point, reflection_intersected_sphere->center, '-');
// 			normal = normalize(normal);
// 			int reflected_color = fade_color(reflection_intersected_sphere->color, dot(shadow_ray, normal) * intersected_sphere->reflectivity);
// 			// *color |= reflected_color;
// 			*color = blend_colors(*color, reflected_color);
// 			cast_reflections(rt, &reflection_ray.dir, &reflection_int_point, reflection_intersected_sphere, color, i - 1);
// 		}
// 	}
// }
