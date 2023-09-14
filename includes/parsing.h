/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:32:54 by svan-de-          #+#    #+#             */
/*   Updated: 2023/09/13 19:40:42 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

# define DOTRT_ERR "Error\nThe scene file must have a .rt extension.\n"
# define FDNM_ERR "Error\nOne of the normal map file cannot be access.\n"

# define SPACE_POINT 	"must have a point in space"
# define INTENSITY		"intensity must range from 0 to 1"
# define SMOOTHNESS		"smoothness must range from 0 to 1"
# define COLOR			"rgb color components must range from 0 to 255"
# define DIAMETER_ERR	"diameter must be positive"
# define SIZE_ERR		"size must be positive"
# define REFLECTION		"reflection arguments must range from 0 to 1"
# define TEXTURE		"texture must be either checkers or a bump map"
# define DIR_VECTOR		"direction vector components must range from -1 to 1"
# define FOV_ERR		"FOV must range from 0 to 180"
# define ST_ERR			"stars option can't be implemented"

enum {
	CHECKERS = 1,
	BUMP_MAP = 2,
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

//NORMAL_MAP

int		*fill_good_maps(char **rows);
int		read_normal_map(t_texture_map *normal_map, char *file_name);
void	load_normal_maps(t_rt *rt, char **rows);

//PARSING

int		print_syntaxe_error(char *obj_type, char *msg, char *example);

int		check_camera(char **row);
int		check_ambuant(char **row);

int		cylinder_cone_optionnal(char **row, int i, int type);
int		check_light(char **row);
int		check_sphere(char **row);
int		check_plan(char **row);
int		check_cylinder(char **row);
int		check_cone(char **row);

int		check_vector_null(char *str);

int		atoi_rgb(char *str);
int		rgb_information(char *str);

int		range_zero_one(char *str);
int		fov_information(char *str);

int		stars_option(char *str);
int		letters_option(char *str);

int		check_double(char *str);
int		check_for_1(char *str);

int		good_chars_vector(char *str);
int		good_coordinate(char *str);
int		vector_coordinates(char *str);
int		good_coordinate_normal(char *str);
int		vector_normal_information(char *str);

void	error_malloc(void);
void	error_information(char *str);
void	error_essential(int n);
void	error_allocation(void);

int		check_argument(int argc, char **argv);

char	*ft_strjoin_free(char *s1, char *s2);
char	check_last_char(char *str);
char	*get_string(int fd);
char	**get_content(int fd);

int		result_type_syntaxe(char **row, t_parsing *parsing);
int		check_type(char *str, t_parsing *parsing);
int		check_essential(char **rows);
void	check_rows(char **rows, t_parsing *parsing);

//FILL

double	conversion_double(char *str);
int		conversion_int(char *str);

void	get_value_vec(char *str, t_vec *vec);
void	get_value_rgb(char *str, t_rgb *rgb);
void	get_letters_options(char *str, int *texture, int *index);

void	fill_ambient(char **row, t_rt *rt);
void	fill_camera(char **row, t_rt *rt);

void	fill_light(char **row, t_info *object);
void	fill_sphere(char **row, t_info *object);
void	fill_plan(char **row, t_info *object);
void	fill_cylinder_cone(char **row, t_info *object);

void	complete_material(t_material *object, t_info *info);
int		create_objects(int material, t_material *object, t_info *info);
int		fill_objects(char **row, t_rt *rt, t_info *info);
void	set_zero(t_info *info);

int		create_objects(int material, t_material *object, t_info *info);
int		fill_objects(char **row, t_rt *rt, t_info *info);
void	fill_rt(char **rows, t_rt *rt, t_parsing parsing);

//BRAIN

void	free_maps(t_texture_map *normal_maps, int *good_maps);
void	set_maps(t_texture_map *normal_maps);
void	free_split(char **split);
void	parsing(int argc, char **argv, t_rt *rt);

#endif