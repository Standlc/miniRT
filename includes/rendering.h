#ifndef RENDERING_H
# define RENDERING_H

#include "minirt.h"

void		set_cam_ray(t_world *world, t_ray *cam_ray, int x, int y);
int			intersect_objects(t_world *world, t_ray *ray, t_hit_info *hit);
void		print_vector(t_vec v);
int			set_hooks(t_rt *rt);
void		reset_rendering(t_rt *rt);
int			render(t_rt *data);
t_rgb		cast_ray(t_world *world, t_ray *ray, int is_specular_ray, int depth);
double  	min(double a, double b);
double  	max(double a, double b);
void		loading_bar(int max, float curr);
void		set_cam_system(t_cam *cam);
void		loader(int frequency, int reset);
double  	get_closest_intersection(double t1, double t2);
t_vec		cosine_hemisphere_dir(t_vec *normal_dir);
t_vec		lerp(t_vec v1, t_vec v2, float t);

// SHADING
t_rgb		indirect_lighting(t_world *world, t_hit_info *hit, int depth);
t_rgb		specular_reflection(t_world *world, t_hit_info *hit, t_ray *ray, int depth);
t_rgb		direct_light_sampling(t_world *world, t_hit_info *hit);
t_rgb		shade_hitpoint(t_world *world, t_hit_info *hit, t_ray *ray, int depth);
void		bump_mapping(t_hit_info *hit);
t_vec		offset_ray_origin(t_hit_info *hit, float offset);


t_vec		normalize(t_vec v);
double  	vec_len(t_vec v);
t_vec		scale(t_vec v, double coef);
double		dot(t_vec *v1, t_vec *v2);
t_vec		get_reflection(t_vec *v, t_vec *normal);
t_vec		cross_product(t_vec *v1, t_vec *v2);
t_vec		get_ray_point(t_ray ray, double d);
t_vec		add(t_vec v1, t_vec v2);
t_vec		sub(t_vec v1, t_vec v2);
t_vec		project(t_vec projected, t_vec reference);
t_vec		system_transform(t_vec *v, t_system *system);
float		get_angle(t_vec *v1, t_vec *normalized);


t_rgb		color_mult(t_rgb color_1, t_rgb color_2);
t_rgb		color_add(t_rgb color_1, t_rgb color_2);
t_rgb		color_fade(t_rgb color, float fade);
int			rgb_to_int(t_rgb rgb);
t_rgb		lerp_color(t_rgb c1, t_rgb c2, float t);
t_rgb		ambient_light(t_rgb *color, t_ray *ray, float intensity);


int			handle_key_down(int key, t_rt *rt);
int			handle_key_up(int key, t_rt *rt);
int			handle_mouse_move(int x, int y, t_rt *rt);
int			handle_mouse_up(int button, int x, int y, t_rt *rt);
int			handle_mouse_down(int button, int x, int y, t_rt *rt);
void		put_pixel(t_rt *data, int x, int y, t_rgb color);


double		pow2(double n);
float		randf();
float		normal_randf();
double  	min(double a, double b);
double		relu(double n);
t_vec		random_dir();


t_system	create_system(t_vec up);
float		checkers(t_vec2 point, float scale);

// SPHERE
t_vec		sample_sphere(void *shape, t_vec *normal_dir);
int			solve_quadratic(t_quadratic *f);
int			create_sphere(t_material *obj, t_info *info);
int 		intersect_circle(t_ray *ray, void *shape, double *t, int *is_surface_hit);

// PLANE
int			intersect_plane(t_ray *ray, void *shape, double *t, int *is_surface_hit);
int			create_plane(t_material *obj, t_info *info);

// CYLINDER
int			create_cylinder(t_material *obj, t_info *info);
t_vec2		cylinder_texture_coordinates(t_hit_info *hit);
int			intersect_cylinder(t_ray *ray, void *shape, double *t, int *is_surface_hit);

// CONE
int			create_cone(t_material *obj, t_info *info);
t_vec2		cone_texture_coordinates(t_hit_info *hit);
int			intersect_cone(t_ray *ray, void *shape, double *t, int *is_surface_hit);

#endif