#include "minirt.h"

void	print_row(char **rows)
{
	for (int i = 0; rows[i]; i++)
		printf("%s\n", rows[i]);
}

void	print_rt(t_rt *rt)
{
	printf("A : %f %f,%f,%f\n", rt->opt.ambient, rt->opt.ambient_light.r, rt->opt.ambient_light.g, rt->opt.ambient_light.b);
	printf("C : %f,%f,%f %f,%f,%f %f\n", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z, rt->cam.look_at.x, rt->cam.look_at.y, rt->cam.look_at.z, rt->cam.field_view);
	// printf("L : %f,%f,%f %f %f,%f,%f\n", &(rt->lights.), );
}

void parsing(int argc, char **argv, t_rt *rt)
{
	t_parsing	parsing;
	char		**rows;

	parsing.fd = check_argument(argc, argv);
	parsing.number_of_materials = 0;
	parsing.number_of_lights = 0;
	rows = get_content(parsing.fd);
	check_rows(rows, &parsing);
	rt->nb_objects = parsing.number_of_materials;
	rt->nb_lights = parsing.number_of_lights;
	fill_rt(rows, rt, parsing);
	print_rt(rt);
	free_split(rows);
	if (close(parsing.fd) == -1)
		(ft_putstr_fd("Error\nThe file cannot be close.\n", 2), exit(errno));
}

// typedef struct	s_rtp {
// 	void			*mlx;
// 	void			*win;
// 	t_img			img;
// 	int				map_height;
// 	int				map_width;
// 	t_cam			cam;
// 	t_rgb			ambient;
//	double			power_ambient;
// 	t_material		*objects;
// 	int         	nb_objects;
// 	t_material		*lights[10];
// 	int         	nb_lights;
// 	t_rgb			pixel_buff[HEIGHT][WIDTH];
// 	t_ray_options	opt;
// 	int				rendering_frame;
// 	t_mouse			mouse;
// 	t_space			space;
// }				t_rtp;

// typedef struct	s_material
// {
// 	t_rgb	color;
// 	float   smoothness;
// 	float	specular_prob;
// 	float	light_intensity;
// 	int		(*intersect)(Ray *, void *, double *);
// 	t_vec	(*normal)(void *, t_vec *, t_vec *);
// 	t_vec	(*light_sample)(void *, Ray *);
// 	void	*shape;
// }				t_material;

//ambient