#include "miniRT.h"

void balls_1(t_rt *rt)
{
	float spec = 0.5;
	static t_sphere sphere1_shape;
	sphere1_shape.center = (t_vec){0, 1.5, -10};
	sphere1_shape.radius = 1.5f;
	rt->objects[0].color = hex_to_rgb(0xffad92);
	// rt->objects[0].color = hex_to_rgb(0xFFFFFF);
	rt->objects[0].smoothness = 1.f;
	rt->objects[0].specular_prob = spec;
	rt->objects[0].light_intensity = 0.f;
	rt->objects[0].shape = (void *)&sphere1_shape;
	rt->objects[0].intersect = intersect_sphere;
	rt->objects[0].normal = sphere_normal;

	static t_sphere light1_shape;
	light1_shape.center = (t_vec){-5, 5, -5};
	light1_shape.radius = 1.f;
	rt->objects[1].shape = (void *)&light1_shape;
	rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	rt->objects[1].light_intensity = 3.f;
	rt->objects[1].intersect = intersect_sphere;
	rt->objects[1].light_sample = sample_sphere;
	rt->objects[1].normal = sphere_normal;

	static t_sphere light2_shape;
	light2_shape.center = (t_vec){5, 5, -5};
	light2_shape.radius = 1.f;
	rt->objects[5].shape = (void *)&light2_shape;
	rt->objects[5].color = hex_to_rgb(0xFFFFFF);
	rt->objects[5].light_intensity = 3.f;
	rt->objects[5].intersect = intersect_sphere;
	rt->objects[5].light_sample = sample_sphere;
	rt->objects[5].normal = sphere_normal;

	static t_sphere sphere4_shape;
	sphere4_shape.center = (t_vec){-3, 2, -13};
	sphere4_shape.radius = 2.f;
	rt->objects[4].color = hex_to_rgb(0xff8feF);
	// rt->objects[4].color = hex_to_rgb(0xFFFFFF);
	rt->objects[4].smoothness = 1.f;
	rt->objects[4].specular_prob = spec;
	rt->objects[4].light_intensity = 0.f;
	rt->objects[4].shape = (void *)&sphere4_shape;
	rt->objects[4].intersect = intersect_sphere;
	rt->objects[4].normal = sphere_normal;

	static t_sphere sphere3_shape;
	sphere3_shape.center = (t_vec){3, 2, -12};
	sphere3_shape.radius = 2.f;
	rt->objects[2].color = hex_to_rgb(0x8287ff);
	// rt->objects[2].color = hex_to_rgb(0xFFFFFF);
	rt->objects[2].smoothness = 1.f;
	rt->objects[2].specular_prob = spec;
	rt->objects[2].light_intensity = 0.f;
	rt->objects[2].shape = (void *)&sphere3_shape;
	rt->objects[2].intersect = intersect_sphere;
	rt->objects[2].normal = sphere_normal;

	static t_sphere sphere5_shape;
	sphere5_shape.center = (t_vec){2, 1, -8};
	sphere5_shape.radius = 1.f;
	rt->objects[6].color = hex_to_rgb(0xFFFFFF);
	rt->objects[6].smoothness = 1.f;
	rt->objects[6].specular_prob = 1.;
	rt->objects[6].light_intensity = 0.f;
	rt->objects[6].shape = (void *)&sphere5_shape;
	rt->objects[6].intersect = intersect_sphere;
	rt->objects[6].normal = sphere_normal;

	static t_sphere light3_shape;
	light3_shape.center = (t_vec){-2, 1, -8};
	light3_shape.radius = 0.5f;
	// rt->objects[7].color = hex_to_rgb(0x0FFF0F);
	// rt->objects[7].color = hex_to_rgb(0xFFFFFF);
	rt->objects[7].color = hex_to_rgb(0);
	rt->objects[7].light_intensity = 0.f;
	rt->objects[7].shape = (void *)&light3_shape;
	rt->objects[7].intersect = intersect_sphere;
	rt->objects[7].normal = sphere_normal;
	rt->objects[7].smoothness = 1.f;
	rt->objects[7].specular_prob = spec;
	rt->objects[7].light_sample = sample_sphere;

	static t_plane plane1_shape;
	plane1_shape.normal = normalize((t_vec){0, 1, 0});
	plane1_shape.point = (t_vec){0, 0, 0};
	rt->objects[3].color = hex_to_rgb(0xFFFFFF);
	rt->objects[3].smoothness = 1.f;
	rt->objects[3].specular_prob = spec;
	rt->objects[3].light_intensity = 0.f;
	rt->objects[3].shape = (void *)&plane1_shape;
	rt->objects[3].intersect = intersect_plane;
	rt->objects[3].normal = plane_normal;

	// rt->opt.ambient = 0.4;
	rt->opt.ambient = 0.;
	rt->nb_objects = 8;
}

void tomato(t_rt *rt)
{
	static t_sphere sphere1_shape;
	sphere1_shape.center = (t_vec){0, 1.5, -10};
	sphere1_shape.radius = 1.5f;
	// 0xff6347
	rt->objects[0].color = hex_to_rgb(0xff6347);
	rt->objects[0].smoothness = 1.f;
	rt->objects[0].specular_prob = 0.3f;
	rt->objects[0].light_intensity = 0.f;
	rt->objects[0].shape = (void *)&sphere1_shape;
	rt->objects[0].intersect = intersect_sphere;
	rt->objects[0].normal = sphere_normal;

	static t_sphere light1_shape;
	light1_shape.center = (t_vec){-4, 5, -10};
	light1_shape.radius = 1.f;
	rt->objects[1].shape = (void *)&light1_shape;
	rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	rt->objects[1].light_intensity = 2.f;
	rt->objects[1].intersect = intersect_sphere;

	static t_plane plane1_shape;
	plane1_shape.normal = normalize((t_vec){0, 1, 0});
	plane1_shape.point = (t_vec){0, 0, 0};
	rt->objects[2].color = hex_to_rgb(0x0);
	rt->objects[2].smoothness = .95f;
	rt->objects[2].specular_prob = .5f;
	rt->objects[2].light_intensity = 0.f;
	rt->objects[2].shape = (void *)&plane1_shape;
	rt->objects[2].intersect = intersect_plane;
	rt->objects[2].normal = plane_normal;

	static t_sphere light2_shape;
	light2_shape.center = (t_vec){5, 5, -5};
	light2_shape.radius = 1.f;
	rt->objects[3].shape = (void *)&light2_shape;
	rt->objects[3].color = hex_to_rgb(0xFFFFFF);
	rt->objects[3].light_intensity = 2.f;
	rt->objects[3].intersect = intersect_sphere;

	rt->nb_objects = 4;
}

void kernel(t_rt *rt)
{
	static t_sphere sphere1_shape;
	sphere1_shape.center = (t_vec){0, 0, -17};
	sphere1_shape.radius = 2.f;
	rt->objects[0].color = hex_to_rgb(0xFF0F5F);
	rt->objects[0].smoothness = 1.f;
	rt->objects[0].specular_prob = 0.5f;
	rt->objects[0].light_intensity = 0.f;
	rt->objects[0].shape = (void *)&sphere1_shape;
	rt->objects[0].intersect = intersect_sphere;
	rt->objects[0].normal = sphere_normal;

	// LITE
	static t_rect rect1_shape;
	rect1_shape.center = (t_vec){0, 4.9, -17};
	rect1_shape.side_a = (t_vec){0, 0, 3};
	rect1_shape.side_b = (t_vec){3, 0, 0};
	rect1_shape.normal = normalize(cross_product(rect1_shape.side_b, rect1_shape.side_a));
	rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	rt->objects[1].smoothness = 0.f;
	rt->objects[1].specular_prob = 0.f;
	rt->objects[1].light_intensity = 3.f;
	rt->objects[1].shape = (void *)&rect1_shape;
	rt->objects[1].intersect = intersect_rect;
	rt->objects[1].normal = rect_normal;
	rt->objects[1].light_sample = sample_rect;

	// static t_sphere	sphereLight;
	// sphereLight.center = (t_vec){0, 6, -17};
	// sphereLight.radius = 2;
	// rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	// rt->objects[1].smoothness = 0.f;
	// rt->objects[1].specular_prob = 0.5f;
	// rt->objects[1].light_intensity = 2.f;
	// rt->objects[1].shape = (void*)&sphereLight;
	// rt->objects[1].intersect = intersect_sphere;
	// rt->objects[1].normal = sphere_normal;
	// rt->objects[1].light_sample = sample_sphere;

	// LEFT & RIGHT
	static t_plane plane1_shape;
	plane1_shape.point = (t_vec){-5, 0, 0};
	plane1_shape.normal = (t_vec){-1, 0, 0};
	rt->objects[2].color = (t_rgb){.75, .25, .25};
	rt->objects[2].smoothness = 1.f;
	rt->objects[2].specular_prob = 0.3f;
	rt->objects[2].light_intensity = 0.f;
	rt->objects[2].shape = (void *)&plane1_shape;
	rt->objects[2].intersect = intersect_plane;
	rt->objects[2].normal = plane_normal;

	static t_plane plane3_shape;
	plane3_shape.normal = normalize((t_vec){-1, 0, 0});
	plane3_shape.point = (t_vec){5, 0, 0};
	rt->objects[3].color = (t_rgb){.25, .25, .75};
	rt->objects[3].smoothness = 1.f;
	rt->objects[3].specular_prob = 0.3f;
	rt->objects[3].light_intensity = 0.f;
	rt->objects[3].shape = (void *)&plane3_shape;
	rt->objects[3].intersect = intersect_plane;
	rt->objects[3].normal = plane_normal;

	// BACK & FRONT
	static t_plane plane4_shape;
	plane4_shape.normal = normalize((t_vec){0, 0, 1});
	plane4_shape.point = (t_vec){0, 0, -25};
	// rt->objects[4].color = hex_to_rgb(0xFFFFFF);
	rt->objects[4].color = hex_to_rgb(0);
	rt->objects[4].smoothness = 1.f;
	rt->objects[4].specular_prob = 0.3f;
	rt->objects[4].light_intensity = 0.f;
	rt->objects[4].shape = (void *)&plane4_shape;
	rt->objects[4].intersect = intersect_plane;
	rt->objects[4].normal = plane_normal;

	static t_plane plane8_shape;
	plane8_shape.normal = normalize((t_vec){0, -1, 0});
	plane8_shape.point = (t_vec){0, 0, 0};
	rt->objects[7].smoothness = 1.f;
	rt->objects[7].specular_prob = 0.3f;
	rt->objects[7].color = (t_rgb){1, 1, 1};
	rt->objects[7].light_intensity = 0.f;
	rt->objects[7].shape = (void *)&plane8_shape;
	rt->objects[7].intersect = intersect_plane;
	rt->objects[7].normal = plane_normal;

	// ROOF & FLOOR
	static t_plane plane5_shape;
	plane5_shape.normal = normalize((t_vec){0, -1, 0});
	plane5_shape.point = (t_vec){0, 5, 0};
	rt->objects[5].smoothness = 1.f;
	rt->objects[5].specular_prob = 0.3f;
	// rt->objects[5].color = (t_rgb){1, 1, 1};
	rt->objects[5].color = hex_to_rgb(0);
	rt->objects[5].light_intensity = 0.f;
	rt->objects[5].shape = (void *)&plane5_shape;
	rt->objects[5].intersect = intersect_plane;
	rt->objects[5].normal = plane_normal;

	static t_plane plane2_shape;
	plane2_shape.normal = normalize((t_vec){0, -1, 0});
	plane2_shape.point = (t_vec){0, -2, 0};
	rt->objects[6].smoothness = 1.f;
	rt->objects[6].specular_prob = 0.3f;
	// rt->objects[6].color = (t_rgb){1, 1, 1};
	rt->objects[6].color = hex_to_rgb(0);
	rt->objects[6].light_intensity = 0.f;
	rt->objects[6].shape = (void *)&plane2_shape;
	rt->objects[6].intersect = intersect_plane;
	rt->objects[6].normal = plane_normal;

	rt->nb_objects = 7;
	rt->opt.ambient = 0.f;
}
