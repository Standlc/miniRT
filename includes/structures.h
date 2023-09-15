/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:42:16 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 18:46:03 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minirt.h"

enum e_events {
	LEFT_CLICK = 1,
	CONTROL = 65513,
	ESC = XK_Escape,
	PRINT = 112,
};

enum e_event_hooks {
	KEY_PRESS = KeyPress,
	KEY_UP = KeyRelease,
	MOUSE_DOWN = ButtonPress,
	MOUSE_UP = ButtonRelease,
	MOUSE_MOVE = MotionNotify
};

enum e_event_mask {
	KEY_PRESS_MASK = KeyPressMask,
	KEY_UP_MASK = KeyReleaseMask,
	MOUSE_DOWN_MASK = ButtonPressMask,
	MOUSE_UP_MASK = ButtonReleaseMask,
	MOUSE_MOVE_MASK = PointerMotionMask
};

typedef struct s_dls {
	double	light_distance;
	float	light_intensity;
	float	normal_shadow_dot;
}				t_dls;

typedef struct s_img {
	void	*p;	
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_vec2 {
	float	x;
	float	y;
}				t_vec2;

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct s_system
{
	t_vec	x;
	t_vec	y;
	t_vec	z;
	t_vec	origin;
}				t_system;

typedef struct s_cam
{
	t_vec		dir;
	t_vec		look_at;
	float		field_view;
	t_system	system;
	float		radius;
}				t_cam;

typedef struct t_ray
{
	t_vec	origin;
	t_vec	dir;
}				t_ray;

typedef struct t_quadratic
{
	double	a;
	double	b;
	double	c;
	double	t_1;
	double	t_2;
}				t_quadratic;

typedef struct s_hit_info	t_hit_info;

typedef struct s_normal_map
{
	t_vec	*map;
	int		height;
	int		width;
}				t_texture_map;

typedef struct s_material
{
	t_rgb			color;
	float			smoothness;
	float			specular_prob;
	float			light_intensity;
	float			hitpoint_offset;
	int				texture;
	int				checkers_scale;
	t_texture_map	*normal_map;
	void			*shape;
	int				(*intersect)(t_ray *ray, void *shape, double *t,
			int *is_surface_hit);
	t_vec			(*normal)(t_hit_info	*hit);
	t_vec2			(*texture_coordinates)(t_hit_info	*hit);
}				t_material;

typedef struct s_hit_info
{
	t_material	*obj;
	t_vec		normal;
	t_vec		hit_point;
	t_vec		bump_normal;
	double		t;
	int			is_specular;
	int			is_surface_hit;
}				t_hit_info;

typedef struct s_plane
{
	t_vec		point;
	t_vec		normal;
	t_system	system;
}				t_plane;

typedef struct s_tri
{
	t_plane	plane;
	t_vec	a;
	t_vec	b;
	t_vec	c;
}				t_tri;

typedef struct s_rect
{
	t_vec	side_a;
	t_vec	side_b;
	t_vec	center;
	t_vec	normal;
}				t_rect;

typedef struct s_circle
{
	t_plane	plane;
	float	radius;
}				t_circle;

typedef struct s_cone
{
	t_circle	base;
	t_vec		center;
	t_vec		dir;
	t_vec		top;
	float		radius;
	float		height;
	t_system	system;
	float		circumference;
}				t_cone;

typedef struct s_sphere
{
	t_vec	center;
	float	radius;
}				t_sphere;

typedef struct s_cylinder
{
	t_circle	covers[2];
	t_vec		center;
	t_vec		dir;
	float		radius;
	float		height;
	t_system	system;
	float		circumference;
}				t_cylinder;

typedef struct s_mouse
{
	t_vec2	origin;
	int		is_down;
}				t_mouse;

typedef struct s_world
{
	t_cam		cam;
	t_material	*objects;
	int			nb_objects;
	t_material	**lights;
	int			nb_lights;
	float		ambient;
	t_rgb		ambient_light;
	int			display_stars;
}				t_world;

typedef struct s_rt {
	void			*mlx;
	void			*win;
	t_img			img;
	t_world			world;
	t_rgb			*pixel_buff;
	int				rendering_frame;
	t_mouse			mouse;
	int				is_zoom_key_down;
	t_texture_map	*normal_maps;
	int				nb_normal_maps;
}				t_rt;

typedef struct s_info
{
	t_rgb	color;
	float	smoothness;
	float	specular_prob;
	float	light_intensity;
	t_vec	center;
	t_vec	dir;
	double	radius;
	double	height;
	int		texture;
	int		texture_selection;
}				t_info;

typedef struct s_parsing
{
	int	fd;
	int	number_of_materials;
	int	number_of_lights;
}	t_parsing;

#endif