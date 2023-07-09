#include "minirt.h"

// blendedValue=(1−𝑡)⋅startValue+𝑡⋅endValue

t_rgb	hex_to_rgb(int hex)
{
	t_rgb	rgb;

	rgb.r = (hex >> 16) / 255.0f;
	rgb.g = ((hex & 0x00FF00) >> 8) / 255.0f;
	rgb.b = (hex & 0x0000FF) / 255.0f;
	return (rgb);
}

// vec3 numerator = v * (1.0f + (v / vec3(max_white * max_white)));
// return numerator / (1.0f + v);

// t_rgb	aces_approx(t_rgb col)
// {	
// 	float a = 2.51f;
// 	float b = 0.03f;
// 	float c = 2.43f;
// 	float d = 0.59f;
// 	float e = 0.14f;

// 	col.r *= 0.6f;
// 	col.g *= 0.6f;
// 	col.b *= 0.6f;

// 	t_rgb	res;
// 	res.r = min((col.r * (a * col.r + b)) / (col.r * (c * col.r + d) + e) * 1, 1.f);
// 	res.g = min((col.g * (a * col.g + b)) / (col.g * (c * col.g + d) + e) * 1, 1.f);
// 	res.b = min((col.b * (a * col.b + b)) / (col.b * (c * col.b + d) + e) * 1, 1.f);
// 	return (res);
// }

int rgb_to_int(t_rgb rgb)
{
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;

	// rgb = aces_approx(rgb);

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
	// return ((t_rgb){color_1.r * color_2.r, color_1.g * color_2.g, color_1.b * color_2.b});
}

t_rgb	color_add(t_rgb color_1, t_rgb color_2)
{
	color_1.r += color_2.r;
	color_1.g += color_2.g;
	color_1.b += color_2.b;
	return (color_1);
	// return ((t_rgb){color_1.r + color_2.r, color_1.g + color_2.g, color_1.b + color_2.b});
}

t_rgb	lerp_color(t_rgb c1, t_rgb c2, float t)
{
	c1.r = (1 - t) * c1.r + t * c2.r;
	c1.g = (1 - t) * c1.g + t * c2.g;
	c1.b = (1 - t) * c1.b + t * c2.b;
	return (c1);
}

t_rgb	ambient_light(Ray *ray)
{
	return (lerp_color((t_rgb){1.f, 1.f, 1.f}, 
						(t_rgb){.8f, .8f, 1.f}, 
						ray->dir.y * 0.5 + 0.5));
}

t_rgb	color_fade(t_rgb color, float fade)
{
	color.r *= fade;
	color.g *= fade;
	color.b *= fade;
	return (color);
	// return ((t_rgb){color.r * fade, color.g * fade, color.b * fade});
}
