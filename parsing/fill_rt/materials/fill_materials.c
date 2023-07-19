#include "minirt.h"

void    fill_light(char **row, t_info *light)
{
    get_value_vec(row[1], &(light->center));
    light->light_intensity = conversion_double(row[2]);
    get_value_rgb(row[3], &(light->color));
    if (row[4])
        light->radius = conversion_double(row[4]) / 2;
    else
        light->radius = 1;
}

void    fill_sphere(char **row, t_info *sphere)
{
    get_value_vec(row[1], &(sphere->center));
    sphere->radius = conversion_double(row[2]) / 2;
    get_value_rgb(row[3], &(sphere->color));
    if (row[4])
        sphere->smoothness = conversion_double(row[4]);
    if (row[4] && row[5])
        sphere->specular_prob = conversion_double(row[5]);
    if (row[4] && row[5] && row[6])
        get_letters_options(row[6], &(sphere->procedural_texturing), &(sphere->bump_mapping));
}

void    fill_plan(char **row, t_info *plan)
{
    get_value_vec(row[1], &(plan->center));
    get_value_vec(row[2], &(plan->dir));
    get_value_rgb(row[3], &(plan->color));
    if (row[4])
        plan->smoothness = conversion_double(row[4]);
    if (row[4] && row[5])
        plan->specular_prob = conversion_double(row[5]);
    if (row[4] && row[5] && row[6])
        get_letters_options(row[6], &(plan->procedural_texturing), &(plan->bump_mapping));
}

void    fill_cylinder_cone(char **row, t_info *cylinder_cone)
{
    get_value_vec(row[1], &(cylinder_cone->center));
    get_value_vec(row[2], &(cylinder_cone->dir));
    cylinder_cone->radius = conversion_double(row[3]) / 2.0;
    cylinder_cone->height = conversion_double(row[4]);
    get_value_rgb(row[5], &(cylinder_cone->color));
    if (row[6])
        cylinder_cone->smoothness = conversion_double(row[6]);
    if (row[6] && row[7])
        cylinder_cone->specular_prob = conversion_double(row[7]);
    if (row[6] && row[7] && row[8])
        get_letters_options(row[8], &(cylinder_cone->procedural_texturing), &(cylinder_cone->bump_mapping));
}
