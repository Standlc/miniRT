#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#define WIDTH       850
#define HEIGHT      500
#define RPP			500
#define MAX_DEPTH	8
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

typedef struct	s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

typedef struct	s_vec
{
	double x;
	double y;
	double z;
}				t_vec;

typedef struct	s_space
{
	t_vec	x;
	t_vec	y;
	t_vec	z;
}				t_space;

typedef struct  s_cam {
	t_vec	pos;
	t_vec	look_at;
	float	field_view;
	float   aspect_ratio;
	int     screen_width;
	int     screen_height;
	t_space	space;
	float	matrix[3][3];
}               t_cam;

typedef struct	Ray
{
	t_vec origin;
	t_vec dir;
}				Ray;

typedef struct	Quadratic_fun
{
	double a;
	double b;
	double c;
}				Quadratic_fun;

typedef struct	s_material
{
	t_rgb	color;
	float   smoothness;
	float	specular_prob;
	float	light_intensity;
	int		(*intersect)(Ray *, void *, double *);
	t_vec	(*normal)(void *, t_vec *, t_vec *);
	t_vec	(*light_sample)(void *);
	void	*shape;
}				t_material;

typedef struct	s_plane
{
	t_vec	point;
	t_vec	normal;
}				t_plane;

typedef struct	s_tri
{
	t_plane	plane;
	t_vec	a;
	t_vec	b;
	t_vec	c;
}				t_tri;

typedef struct	s_rect
{
	t_vec	side_a;
	t_vec	side_b;
	t_vec	center;
	t_vec	normal;
}				t_rect;

typedef struct	s_sphere
{
	t_vec	center;
	float	radius;
}				t_sphere;

typedef struct	s_delta_light
{
	t_vec	pos;
	t_rgb	color;
	float	intensity;
}				t_delta_light;

typedef struct	s_mouse
{
	t_point	origin;
	int		is_down;
}				t_mouse;

typedef struct	s_ray_options
{
	int		max_depth;
	int		rpp;
	int		n_shadow_rays;
	float	ambient;
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

enum {
	AMBIENT = 1,
	CAMERA = 2,
	LIGHT = 3,
	SPHERE = 4,
	PLAN = 5,
	CYLINDRER = 6,
};

// SCENES
void    balls_1(t_rt *rt);
void    tomato(t_rt *rt);
void    kernel(t_rt *rt);
void	print_vector(t_vec v);


int		render(t_rt *data);
double  min(double a, double b);
void	loading_bar(int max, float curr);
void	set_cam(t_rt *data);
void	loader(int frequency);
void	clear_pixel_buff(t_rgb pixel_buff[HEIGHT][WIDTH]);
double  get_closest_intersection(double t1, double t2);


t_vec	normalize(t_vec v);
double  vec_len(t_vec v);
t_vec	scale(t_vec v, double coef);
double	dot(t_vec v1, t_vec v2);
t_vec	vect_op(t_vec v1, char operation, t_vec v2);
t_vec	get_reflection(t_vec *v, t_vec *normal);
t_vec	cross_product(t_vec v1, t_vec v2);
t_vec	get_ray_point(Ray ray, double d);
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2);
t_vec	mult(t_vec v1, t_vec v2);
t_vec	project(t_vec projected, t_vec reference);


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
t_vec	random_dir();


// SPHERE
t_vec	sphere_normal(void *shape, t_vec *ray_dir, t_vec *hit_point);
int		intersect_sphere(Ray *ray, void *shape, double *t);
t_vec	sample_sphere(void *shape);


// PLANE
int		intersect_plane(Ray *ray, void *shape, double *t);
t_vec	plane_normal(void *shape, t_vec *ray_dir, t_vec *hit_point);


// RECTANGLE
int		intersect_rect(Ray *ray, void *shape, double *t);
t_vec	rect_normal(void *shape, t_vec *ray_dir, t_vec *hit_point);
t_vec	sample_rect(void *shape);

//PARSING

int check_camera(char **row);
int check_ambuant(char **row);

int check_light(char **row);
int check_sphere(char **row);
int check_plan(char **row);
int check_cylinder(char **row);

int	atoi_rgb(char *str);
int	rgb_information(char *str);
int	range_zero_one(char *str);

void	error_malloc();
void	error_information();

int		check_argument(int argc, char **argv);

char	*ft_strjoin_free(char *s1, char *s2);
char	check_last_char(char *str);
char    *get_string(int fd);
char	**get_content(int fd);

void	check_rows(char **rows);
void	print_row(char **rows);
void	free_split(char **split);

#endif