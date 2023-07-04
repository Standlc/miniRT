#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "mlx.h"

#define WIDTH       1000
#define HEIGHT      500
#define ON_DESTROY  17
#define MIRROR      1
#define SOLID       2
#define	ZERO		1e-6

typedef struct	s_img {
	void	*p;	
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point {
	double  x;
	double  y;
} t_point;

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
} t_rgb;

typedef struct Vector
{
	double x;
	double y;
	double z;
} Vector;

typedef struct	s_space
{
	Vector	x;
	Vector	y;
	Vector	z;
}				t_space;

typedef struct  s_cam {
	Vector  pos;
	Vector	look_at;
	float	field_view;
	float   aspect_ratio;
	int     screen_width;
	int     screen_height;
	t_space	space;
	float	matrix[3][3];
}               t_cam;

typedef struct	Ray
{
	Vector origin;
	Vector dir;
}				Ray;

typedef struct	Quadratic_fun
{
	double a;
	double b;
	double c;
}				Quadratic_fun;

typedef struct	s_material
{
	int     type;
	t_rgb	color;
	float   smoothness;
	float	specular_prob;
	float	light_entensity;
	int		(*intersect)(Ray *, struct s_material *, double *);
	Vector	(*normal)(struct s_material *, Vector *, Vector *);
	void	*shape;
}				t_material;

typedef struct	s_plane
{
	Vector	normal;
	Vector	point;
}				t_plane;

typedef struct	s_tri
{
	t_plane	plane;
	Vector	a;
	Vector	b;
	Vector	c;
}				t_tri;

typedef struct	s_sphere
{
	Vector		center;
	float		radius;
}				t_sphere;

typedef struct	s_delta_light
{
	Vector  pos;
	t_rgb	color;
	float	intensity;
}				t_delta_light;

typedef struct	s_mouse
{
	t_point	origin;
	t_point	dir;
	int		is_down;
}				t_mouse;

typedef struct	s_ray_options
{
	int		max_depth;
	int		rays_per_pixel;
	int		n_shadow_rays;
	float	cam_ray_fuzz;
	float	gamma;
}				t_ray_options;

typedef struct	s_rt {
	void			*mlx;
	void			*win;
	t_img			img;
	int				map_height;
	int				map_width;
	t_cam			cam;
	t_material		objects[20];
	int         	nb_objects;
	t_material		*lights[10];
	int         	nb_lights;
	t_rgb			pixel_buff[HEIGHT][WIDTH];
	t_ray_options	opt;
	int				rendering_frame;
	t_mouse			mouse;
	t_space			space;
}				t_rt;

enum {
	//LINUX KEYS
	// UP = 65362, 
	// DOWN = 65364, 
	// RIGHT = 65363, 
	// LEFT = 65361, 
	// ZOOM_IN = 61,
	// ZOOM_OUT = 45,
	// SCROLL_UP = 4,
	// SCROLL_DOWN = 5,
	// RESET = 114,
	// ESC = 65307,

	//MACOS KEYS
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	ZOOM_IN = 24,
	ZOOM_OUT = 27,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
	RESET = 15,
	ESC = 53,
};

// SCENES
void    balls_1(t_rt *rt);
void    tomato(t_rt *rt);
void	print_vector(Vector v);

int		render(t_rt *data);
double  min(double a, double b);
void	loading_bar(int max, float curr);
void	set_cam(t_rt *data);
void	loader(int frequency);
void	clear_pixel_buff(t_rgb pixel_buff[HEIGHT][WIDTH]);
double  get_closest_intersection(double t1, double t2);


Vector	normalize(Vector v);
double  vector_len(Vector v);
Vector	scale(Vector v, double coef);
double	dot(Vector v1, Vector v2);
Vector	vect_op(Vector v1, char operation, Vector v2);
Vector  get_reflection(Vector *v, Vector *normal);
Vector	cross_product(Vector v1, Vector v2);
Vector  get_line_point(Ray ray, double d);
Vector	add(Vector v1, Vector v2);
Vector	minus(Vector v1, Vector v2);
Vector	mult(Vector v1, Vector v2);


t_rgb	hex_to_rgb(int hex);
t_rgb	color_mult(t_rgb color_1, t_rgb color_2);
t_rgb	color_add(t_rgb color_1, t_rgb color_2);
t_rgb	color_fade(t_rgb color, float fade);
int		rgb_to_int(t_rgb rgb);
t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t);
t_rgb	ambient_light(Ray *ray);


int		handle_key(int key, t_rt *data);
int		handle_mouse_move(int x, int y, t_rt *rt);
int		handle_mouse_up(int button, int x, int y, t_rt *rt);
int		handle_mouse(int event, int x, int y, t_rt *rt);
int		close_program(t_rt *data);
void	put_pixel(t_rt *data, int x, int y, t_rgb color);


float	randf();
float	normal_randf();
double  min(double a, double b);
double	relu(double n);


// SPHERE
Vector	sphere_normal(t_material *obj, Vector *ray_dir, Vector *hit_point);
int		intersect_sphere(Ray *ray, t_material *obj, double *intersection_t);


// PLANE
int		intersect_plane(Ray *ray, t_material *obj, double *t);
Vector	plane_normal(t_material *obj, Vector *ray_dir, Vector *hit_point);


#endif