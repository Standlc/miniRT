#include "minirt.h"

t_rgb	hex_to_rgb(int hex)
{
	t_rgb	rgb;

	rgb.r = (hex >> 16) / 255.0f;
	rgb.g = ((hex & 0x00FF00) >> 8) / 255.0f;
	rgb.b = (hex & 0x0000FF) / 255.0f;
	return (rgb);
}

int rgb_to_int(t_rgb rgb)
{
    unsigned char	r;
    unsigned char	g;
    unsigned char	b;

    r = min(rgb.r, 1.) * 255;
    g = min(rgb.g, 1.) * 255;
    b = min(rgb.b, 1.) * 255;
    return (r << 16 | g << 8 | b);
}

t_rgb	color_mult(t_rgb color_1, t_rgb color_2)
{
	color_1.r *= color_2.r;
	color_1.g *= color_2.g;
	color_1.b *= color_2.b;
	return (color_1);
}

t_rgb	color_add(t_rgb color_1, t_rgb color_2)
{
	color_1.r += color_2.r;
	color_1.g += color_2.g;
	color_1.b += color_2.b;
	return (color_1);
}

t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t)
{
	c1.r = (1 - t) * c1.r + t * c2.r;
	c1.g = (1 - t) * c1.g + t * c2.g;
	c1.b = (1 - t) * c1.b + t * c2.b;
	return (c1);
}

t_rgb	color_sub(t_rgb color, float sub)
{
	color.r = max(color.r - sub, 0.0);
	color.g = max(color.g - sub, 0.0);
	color.b = max(color.b - sub, 0.0);
	return (color);
}

t_rgb	ambient_light(t_rgb *color, t_ray *ray, float intensity)
{
	// return (lerp_color((t_rgb){0, 0, 1}, (t_rgb){1, 0, 0}, ray->dir.y * 0.5 + 0.5));
	return (
		lerp_color(
				lerp_color(color_sub(*color, 1 - intensity), (t_rgb){1.f, 1.f, 1.f}, intensity),
				lerp_color(color_sub(*color, 1 - intensity), *color, intensity),
				ray->dir.y * 0.5 + 0.5
			)
		);
}

t_rgb	color_fade(t_rgb color, float fade)
{
	color.r *= fade;
	color.g *= fade;
	color.b *= fade;
	return (color);
}
