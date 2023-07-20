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
#define	ZERO		0.0

enum textures {
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
	AMBIENT = 1,
	CAMERA = 2,
	LIGHT = 3,
	SPHERE = 4,
	PLAN = 5,
	CYLINDER = 6,
	CONE = 7,
};

#include "events.h"
#include "rendering.h"

//PARSING
int		read_normal_map(t_normal_map *normal_map, char *file_name);

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
