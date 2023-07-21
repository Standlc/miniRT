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

void    get_letters_options(char *str, int *texture, int *index)
{
    if (!ft_strncmp(str, "ch", 3))
    {
        *texture = CHECKERS;
        return ;
    }
    if (!ft_strncmp(str, "bm-1", 5))
        *index = 0;
    if (!ft_strncmp(str, "bm-2", 5))
        *index = 1;
    if (!ft_strncmp(str, "bm-3", 5))
        *index = 2;
    if (!ft_strncmp(str, "bm-4", 5))
        *index = 3;
    if (!ft_strncmp(str, "bm-5", 5))
        *index = 4;
    *texture = BUMP_MAP;
}