#include "minirt.h"

void    fill_ambient(char **row, t_rt *rt)
{
    rt->opt.ambient = conversion_double(row[1]);
    get_value_rgb(row[2], &(rt->opt.ambient_light));
}

void    fill_camera(char **row, t_rt *rt)
{
    get_value_vec(row[1], &(rt->cam.system.origin));
    get_value_vec(row[2], &(rt->cam.look_at));
    rt->cam.field_view = (double)conversion_int(row[3]);
}