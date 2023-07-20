#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#define WIDTH       850
#define HEIGHT      500
#define RPP			500
#define MAX_DEPTH	10
#define ON_DESTROY  17
#define MIRROR      1
#define SOLID       2
// #define	ZERO		1e-6
#define	ZERO		0.0

enum {
	CHECKERS = 1,
	BUMP_MAP = 2,
};

typedef struct	s_dls {
	float	distance_from_ray_origin;
	double	light_distance;
	float	light_intensity;
	float	normal_shadow_dot;
	int		indirect_decay;
}				t_dls;

typedef struct	s_img {
	void	*p;	
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_vec2 {
	float	x;
	float	y;
}				t_vec2;

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

typedef struct	s_system
{
	t_vec	x;
	t_vec	y;
	t_vec	z;
	t_vec	origin;
}				t_system;

typedef struct  s_cam {
	t_vec		dir;
	t_vec		look_at;
	float		field_view;
	float   	aspect_ratio;
	t_system	system;
	float		radius;
}               t_cam;

typedef struct	t_ray
{
	t_vec origin;
	t_vec dir;
}				t_ray;

typedef struct	t_quadratic
{
	double a;
	double b;
	double c;
}				t_quadratic;

typedef struct	s_hit_info t_hit_info;

typedef struct	s_normal_map
{
	t_vec	*map;
	int		height;
	int		width;
}				t_normal_map;

typedef struct	s_material
{
	t_rgb			color;
	float   		smoothness;
	float			specular_prob;
	float			light_intensity;
	int				texture;
	t_normal_map	*normal_map;
	void			*shape;
	int				(*intersect)(t_ray *ray, void *shape, double *t, int *is_surface_hit);
	t_vec			(*normal)(t_hit_info *hit);
	t_vec2			(*texture_coordinates)(t_hit_info *hit, int keep_ratio);
}				t_material;

typedef struct	s_hit_info
{
	t_material	obj;
	t_vec		normal;
	t_vec		hit_point;
	t_vec		bump_normal;
	double		t;
	int			is_specular;
	int			is_surface_hit;
}				t_hit_info;

typedef struct	s_plane
{
	t_vec		point;
	t_vec		normal;
	t_system	system;
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

typedef struct	s_circle
{
	t_plane	plane;
	float	radius;
}				t_circle;

typedef struct	s_cone
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

typedef struct	s_sphere
{
	t_vec	center;
	float	radius;
}				t_sphere;

typedef struct	s_cylinder
{
	t_circle	covers[2];
	t_vec		center;
	t_vec		dir;
	float		radius;
	float		height;
	t_system	system;
	float		circumference;
}				t_cylinder;

typedef struct	s_mouse
{
	t_vec2	origin;
	int		is_down;
}				t_mouse;

typedef struct	s_ray_options
{
	int		max_depth;
	int		rpp;
	float	ambient;
	t_rgb	ambient_light;
	float	cam_ray_fuzz;
	float	gamma;
	int		pixel_rendered_interval;
}				t_ray_options;

typedef struct	s_rt {
	void			*mlx;
	void			*win;
	t_img			img;
	t_cam			cam;
	t_material		*objects;
	int         	nb_objects;
	t_material		**lights;
	int         	nb_lights;
	t_rgb			*pixel_buff;
	t_ray_options	opt;
	int				rendering_frame;
	t_mouse			mouse;
	t_system		system;
	t_normal_map	*normal_maps;
	int				nb_normal_maps;
	int				is_zoom_key_down;
}				t_rt;

typedef struct	s_info
{
	t_rgb	color;
	float   smoothness;
	float	specular_prob;
	float	light_intensity;
	t_vec	center;
	t_vec	dir;
	double	radius;
	double	height;
	int		procedural_texturing;
	int		bump_mapping;
}				t_info;

typedef struct	s_parsing
{
	int	fd;
	int	number_of_materials;
	int	number_of_lights;
}	t_parsing;

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
	CYLINDER = 6,
	CONE = 7,
};

// NORMAL MAP
int	read_normal_map(t_normal_map *normal_map, char *file_name);

// SCENES
void	print_vector(t_vec v);
void	print_system(t_system s);

void	stop_optimization(t_rt *rt);
void	start_optimization(t_rt *rt);
void	rotate_camera(t_rt *rt, int mouse_dir_x, int mouse_dir_y);
int	set_hooks(t_rt *rt);
void	reset_rendering(t_rt *rt);

int		render(t_rt *data);
t_rgb	cast_ray(t_rt *rt, t_ray *ray, int is_specular_ray, int depth);
double  min(double a, double b);
double  max(double a, double b);
void	loading_bar(int max, float curr);
void	set_cam_system(t_rt *data);
void	loader(int frequency);
double  get_closest_intersection(double t1, double t2);
t_vec	cosine_hemisphere_dir(t_vec *normal_dir);
t_vec	lerp(t_vec v1, t_vec v2, float t);
int	points_inwards(t_hit_info *hit, t_vec *ray_dir);


// SHADING
t_rgb	cast_ray(t_rt *rt, t_ray *ray, int is_specular_ray, int depth);
t_rgb	indirect_lighting(t_rt *rt, t_hit_info *hit, int depth);
t_rgb	specular_lighting(t_rt *rt, t_hit_info *hit, t_ray *ray, int depth);
t_rgb	direct_light_sampling(t_rt *rt, t_ray *ray, t_hit_info *hit, int indirect_decay);
t_rgb	shade_hitpoint(t_rt *rt, t_hit_info *hit, t_ray *ray, int depth);
t_vec	bump_mapping(t_hit_info *hit);
t_vec	offset_ray_origin(t_hit_info *hit);


t_vec	normalize(t_vec v);
double  vec_len(t_vec v);
t_vec	scale(t_vec v, double coef);
double	dot(t_vec v1, t_vec v2);
t_vec	get_reflection(t_vec *v, t_vec *normal);
t_vec	cross_product(t_vec v1, t_vec v2);
t_vec	get_ray_point(t_ray ray, double d);
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2);
t_vec	project(t_vec projected, t_vec reference);
t_vec	system_transform(t_vec v, t_system system);
float	get_angle(t_vec *v1, t_vec *v2);


t_rgb	hex_to_rgb(int hex);
t_rgb	color_mult(t_rgb color_1, t_rgb color_2);
t_rgb	color_add(t_rgb color_1, t_rgb color_2);
t_rgb	color_fade(t_rgb color, float fade);
int		rgb_to_int(t_rgb rgb);
t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t);
t_rgb	ambient_light(t_rgb color, t_ray *ray, float intensity);


int	handle_key_down(int key, t_rt *rt);
int	handle_key_up(int key, t_rt *rt);
int		handle_mouse_move(int x, int y, t_rt *rt);
int		handle_mouse_up(int button, int x, int y, t_rt *rt);
int		handle_mouse_down(int button, int x, int y, t_rt *rt);
void	free_object(t_material *object);
void	free_elements(t_rt *rt);
int		close_program(t_rt *data);
void	put_pixel(t_rt *data, int x, int y, t_rgb color);
void	start_optimization(t_rt *rt);


float	randf();
float	normal_randf();
double  min(double a, double b);
double	relu(double n);
t_vec	random_dir();


t_system	create_system(t_vec up);
float	checkers(t_vec2 point, float scale);

// SPHERE
t_vec	sample_sphere(void *shape, t_vec *normal_dir);
int		solve_quadratic(t_quadratic f, double *x1, double *x2);
int		create_sphere(t_material *obj, t_info *info);
int intersect_circle(t_ray *ray, void *shape, double *t, int *is_surface_hit);


// PLANE
int	intersect_plane(t_ray *ray, void *shape, double *t, int *is_surface_hit);
int		create_plane(t_material *obj, t_info *info);


// CYLINDER
int		create_cylinder(t_material *obj, t_info *info);


// CONE
int		create_cone(t_material *obj, t_info *info);


//PARSING

int check_camera(char **row);
int check_ambuant(char **row);

int check_light(char **row);
int check_sphere(char **row);
int check_plan(char **row);
int check_cylinder(char **row);
int check_cone(char **row);

int	atoi_rgb(char *str);
int	rgb_information(char *str);

int	range_zero_one(char *str);
int	fov_information(char *str);

int	letters_option(char *str);

int check_double(char *str);
int check_for_1(char *str);

int good_chars_vector(char *str);
int good_coordinate(char *str);
int vector_coordinates(char *str);
int good_coordinate_normal(char *str);
int vector_normal_information(char *str);

void	error_malloc();
void	error_information(char *str);
void	error_essential();
void    error_allocation();

int		check_argument(int argc, char **argv);

char	*ft_strjoin_free(char *s1, char *s2);
char	check_last_char(char *str);
char    *get_string(int fd);
char	**get_content(int fd);

int		result_type_syntaxe(char **row, t_parsing *parsing);
int		check_type(char *str, t_parsing *parsing);
int	check_essential(char **rows);
void	check_rows(char **rows, t_parsing *parsing);

//FILL

double	conversion_double(char *str);
int		conversion_int(char *str);

void	get_value_vec(char *str, t_vec *vec);
void    get_value_rgb(char *str, t_rgb *rgb);
void    get_letters_options(char *str, int *procedural_texturing, int *bump_mapping);

void    fill_ambient(char **row, t_rt *rt);
void    fill_camera(char **row, t_rt *rt);

void    fill_light(char **row, t_info *object);
void    fill_sphere(char **row, t_info *object);
void    fill_plan(char **row, t_info *object);
void    fill_cylinder_cone(char **row, t_info *object);

int		create_objects(int material, t_material *object, t_info *info);
int		fill_objects(char **row, t_rt *rt, t_info *info);
void	fill_rt(char **rows, t_rt *rt, t_parsing parsing);

//BRAIN

void	free_split(char **split);
void	parsing(int argc, char **argv, t_rt *rt);

#endif
