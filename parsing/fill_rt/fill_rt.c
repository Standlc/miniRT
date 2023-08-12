#include "minirt.h"

void	complete_material(t_material *object, t_info *info)
{
	object->color = info->color;
	object->light_intensity = info->light_intensity;
	object->smoothness = info->smoothness;
	object->specular_prob = info->specular_prob;
}

int	create_objects(int material, t_material *object, t_info *info)
{
	if (material == LIGHT)
		return (create_sphere(object, info));
	if (material == SPHERE)
		return (create_sphere(object, info));
	if (material == PLAN)
		return (create_plane(object, info));
	if (material == CYLINDER)
		return (create_cylinder(object, info));
	if (material == CONE)
		return (create_cone(object, info));
	return (0);
}

int	fill_objects(char **row, t_rt *rt, t_info *info)
{
	if (!ft_strncmp(row[0], "A", 2))
		return (fill_ambient(row, rt), AMBIENT);
	if (!ft_strncmp(row[0], "C", 2))
		return (fill_camera(row, rt), CAMERA);
	if (!ft_strncmp(row[0], "L", 2))
		return (fill_light(row, info), LIGHT);
	if (!ft_strncmp(row[0], "sp", 3))
		return (fill_sphere(row, info), SPHERE);
	if (!ft_strncmp(row[0], "pl", 3))
		return (fill_plan(row, info), PLAN);
	if (!ft_strncmp(row[0], "cy", 3))
		return (fill_cylinder_cone(row, info), CYLINDER);
	if (!ft_strncmp(row[0], "co", 3))
		return (fill_cylinder_cone(row, info), CONE);
	return (0);
}

void    set_zero(t_info *info)
{
    info->color.r = 0;
    info->color.g = 0;
    info->color.b = 0;
    info->smoothness = 0;
    info->specular_prob = 0;
    info->light_intensity = 0;
    info->center.x = 0;
    info->center.y = 0;
    info->center.z = 0;
    info->dir.x = 0;
    info->dir.y = 0;
    info->dir.z = 0;
    info->radius = 0;
    info->height = 0;
    info->texture = 0;
	info->texture_selection = 0;
}

// void	print_obj(t_material *obj)
// {
// 	printf("color : %f,%f,%f\n", obj->color.r, obj->color.g, obj->color.b);
// 	printf("smooth : %f\n", obj->smoothness);
// 	printf("spec : %f\n", obj->specular_prob);
// 	printf("intensity : %f\n", obj->light_intensity);
// 	printf("intersect : %p\n", obj->intersect);
// 	printf("normal : %p\n", obj->normal);
// 	printf("texture_coordinates : %p\n", obj->texture_coordinates);
// }

void	fill_rt(char **rows, t_rt *rt, t_parsing parsing)
{
	int		i;
	int		index_light;
	int		index_objects;
	int		material;
	char	**row;
	t_info	info;

	i = 0;
	index_light = 0;
	index_objects = 0;
	rt->world.objects = malloc(sizeof(t_material) * parsing.number_of_materials);
	rt->world.lights = malloc(sizeof(t_material *) * parsing.number_of_lights);
	if (!rt->world.objects || !rt->world.lights)
		(free(rt->world.objects), free(rt->world.lights), free_split(rows), exit(1));
	while (rows[i])
	{
		row = ft_split(rows[i], ' ');
		if (!row)
			(free_split(rows), free(rt->world.objects), exit(1));
		set_zero(&info);
		material = fill_objects(row, rt, &info);
		if (material != AMBIENT && material != CAMERA)
		{
			if (info.texture == BUMP_MAP)
				rt->world.objects[index_objects].normal_map = rt->normal_maps + info.texture_selection;
			else
				rt->world.objects[index_objects].normal_map = NULL;
			if (info.texture == CHECKERS)
				rt->world.objects[index_objects].checkers_scale = info.texture_selection;
			else
				rt->world.objects[index_objects].checkers_scale = 0;
			if (create_objects(material, rt->world.objects + index_objects, &info))
				(free_split(row), free_split(rows), free(rt->world.objects), exit(1));
			complete_material(rt->world.objects + index_objects++, &info);
			if (material == LIGHT)
				rt->world.lights[index_light++] = rt->world.objects + (index_objects - 1);
		}
		free_split(row);
		i++;
	}
}