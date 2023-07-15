#include "minirt.h"

void    fill_light(char **row, t_info *light)
{
    get_value_vec(row[1], &(light->center));
    light->light_intensity = conversion_double(row[2]);
    get_value_rgb(row[3], &(light->color));
    light->radius = 1.0;
    light->procedural_texturing = 0;
}

void    fill_sphere(char **row, t_info *sphere)
{
    get_value_vec(row[1], &(sphere->center));
    sphere->radius = conversion_double(row[2]) / 2.0;
    get_value_rgb(row[3], &(sphere->color));
    if (row[4])
    {
        sphere->smoothness = conversion_double(row[4]);
        if (row[5])
            sphere->specular_prob = conversion_double(row[5]);
        else
            sphere->specular_prob = 0;
    }
    else
        sphere->smoothness = 0;
    sphere->procedural_texturing = !ft_strncmp("d", row[6], 1);
    sphere->light_intensity = 0;
}

void    fill_plan(char **row, t_info *plan)
{
    get_value_vec(row[1], &(plan->center));
    get_value_vec(row[2], &(plan->dir));
    get_value_rgb(row[3], &(plan->color));
    if (row[4])
    {
        plan->smoothness = conversion_double(row[4]);
        if (row[5])
            plan->specular_prob = conversion_double(row[5]);
        else
            plan->specular_prob = 0;
    }
    else
        plan->smoothness = 0;
    plan->light_intensity = 0;
    plan->procedural_texturing = 0;
}

void    fill_cylinder_cone(char **row, t_info *cylinder_cone)
{
    get_value_vec(row[1], &(cylinder_cone->center));
    get_value_vec(row[2], &(cylinder_cone->dir));
    cylinder_cone->radius = conversion_double(row[3]) / 2.0;
    cylinder_cone->height = conversion_double(row[4]);
    get_value_rgb(row[5], &(cylinder_cone->color));
    if (row[6])
    {
        cylinder_cone->smoothness = conversion_double(row[6]);
        if (row[7])
            cylinder_cone->specular_prob = conversion_double(row[7]);
        else
            cylinder_cone->specular_prob = 0;
    }
    else
        cylinder_cone->smoothness = 0;
    cylinder_cone->light_intensity = 0;
    cylinder_cone->procedural_texturing = 0;
}
