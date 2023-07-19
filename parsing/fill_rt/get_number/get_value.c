#include "minirt.h"

void    get_value_rgb(char *str, t_rgb *rgb)
{
    int i;

    i = 1;
    rgb->r = (double)conversion_int(str) / 255.0;
    while (str[i - 1] != ',')
        i++;
    rgb->g = (double)conversion_int(&str[i]) / 255.0;
    i++;
    while (str[i - 1] != ',')
        i++;
    rgb->b = (double)conversion_int(&str[i]) / 255.0;
}

void    get_value_vec(char *str, t_vec *vec)
{
    int i;

    i = 1;
    vec->x = conversion_double(str);
    while (str[i - 1] != ',')
        i++;
    vec->y = conversion_double(&str[i]);
    i++;
    while (str[i - 1] != ',')
        i++;
    vec->z = conversion_double(&str[i]);
}

void    get_letters_options(char *s1, char *s2, int *procedural_texturing, int *bump_mapping)
{
    *procedural_texturing = 0;
    *bump_mapping = 0;
    if (!ft_strncmp(s1, "ch", 3))
        *procedural_texturing = 1;
    if (!ft_strncmp(s1, "bm", 3))
        *bump_mapping = 1;
    if (!s2)
        return ;
    if (!ft_strncmp(s2, "ch", 3))
        *procedural_texturing = 1;
    if (!ft_strncmp(s2, "bm", 3))
        *bump_mapping = 1;
}