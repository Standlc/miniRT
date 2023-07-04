#include "miniRT.h"

void    balls_1(t_rt *rt)
{
	static t_sphere	sphere1_shape;
	sphere1_shape.center = (Vector){0, 1.5, -10};
	sphere1_shape.radius = 1.5f;
	rt->objects[0].color = hex_to_rgb(0xffad92);
	rt->objects[0].smoothness = 1.f;
	rt->objects[0].specular_prob = 0.5f;
	rt->objects[0].light_entensity = 0.f;
	rt->objects[0].shape = (void*)&sphere1_shape;
	rt->objects[0].intersect = intersect_sphere;
	rt->objects[0].normal = sphere_normal;

	static t_sphere	light1_shape;
	light1_shape.center = (Vector){-5, 5, -5};
	light1_shape.radius = 1.f;
	rt->objects[1].shape = (void*)&light1_shape;
	rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	rt->objects[1].light_entensity = 2.f;
	rt->objects[1].intersect = intersect_sphere;

	static t_sphere	light2_shape;
	light2_shape.center = (Vector){4, 7, -3};
	light2_shape.radius = 1.f;
	rt->objects[5].shape = (void*)&light2_shape;
	rt->objects[5].color = hex_to_rgb(0xFFFFFF);
	rt->objects[5].light_entensity = 2.f;
	rt->objects[5].intersect = intersect_sphere;

	static t_sphere	sphere4_shape;
	sphere4_shape.center = (Vector){-3, 2, -13};
	sphere4_shape.radius = 2.f;
	rt->objects[4].color = hex_to_rgb(0xff8feF);
	rt->objects[4].smoothness = 1.f;
	rt->objects[4].specular_prob = .5f;
	rt->objects[4].light_entensity = 0.f;
	rt->objects[4].shape = (void*)&sphere4_shape;
	rt->objects[4].intersect = intersect_sphere;
	rt->objects[4].normal = sphere_normal;

	static t_sphere	sphere3_shape;
	sphere3_shape.center = (Vector){3, 2, -12};
	sphere3_shape.radius = 2.f;
	rt->objects[2].color = hex_to_rgb(0x8287ff);
	rt->objects[2].smoothness = 1.f;
	rt->objects[2].specular_prob = 0.3f;
	rt->objects[2].light_entensity = 0.f;
	rt->objects[2].shape = (void*)&sphere3_shape;
	rt->objects[2].intersect = intersect_sphere;
	rt->objects[2].normal = sphere_normal;

	static t_sphere	sphere5_shape;
	sphere5_shape.center = (Vector){2, 1, -8};
	sphere5_shape.radius = 1.f;
	rt->objects[6].color = hex_to_rgb(0xFFFFFF);
	rt->objects[6].smoothness = 1.f;
	rt->objects[6].specular_prob = 1.f;
	rt->objects[6].light_entensity = 0.f;
	rt->objects[6].shape = (void*)&sphere5_shape;
	rt->objects[6].intersect = intersect_sphere;
	rt->objects[6].normal = sphere_normal;

	static t_sphere	light3_shape;
	light3_shape.center = (Vector){-2, 1, -8};
	light3_shape.radius = 0.5f;
	rt->objects[7].color = hex_to_rgb(0x0);
	rt->objects[7].light_entensity = 0.f;
	rt->objects[7].shape = (void*)&light3_shape;
	rt->objects[7].intersect = intersect_sphere;
	rt->objects[7].normal = sphere_normal;
	rt->objects[7].smoothness = 1.f;
	rt->objects[7].specular_prob = 0.5f;

	static t_plane	plane1_shape;
	plane1_shape.normal = normalize((Vector){0, 1, 0});
	plane1_shape.point = (Vector){0, 0, 0};
	rt->objects[3].color = hex_to_rgb(0);
	rt->objects[3].smoothness = 1.f;
	rt->objects[3].specular_prob = .2f;
	rt->objects[3].light_entensity = 0.f;
	rt->objects[3].shape = (void*)&plane1_shape;
	rt->objects[3].intersect = intersect_plane;
	rt->objects[3].normal = plane_normal;

	rt->nb_objects = 8;
}

void    tomato(t_rt *rt)
{
	static t_sphere	sphere1_shape;
	sphere1_shape.center = (Vector){0, 1.5, -10};
	sphere1_shape.radius = 1.5f;
    // 0xff6347
	rt->objects[0].color = hex_to_rgb(0xff6347);
	rt->objects[0].smoothness = 1.f;
	rt->objects[0].specular_prob = 0.3f;
	rt->objects[0].light_entensity = 0.f;
	rt->objects[0].shape = (void*)&sphere1_shape;
	rt->objects[0].intersect = intersect_sphere;
	rt->objects[0].normal = sphere_normal;

	static t_sphere	light1_shape;
	light1_shape.center = (Vector){-4, 5, -10};
	light1_shape.radius = 1.f;
	rt->objects[1].shape = (void*)&light1_shape;
	rt->objects[1].color = hex_to_rgb(0xFFFFFF);
	rt->objects[1].light_entensity = 2.f;
	rt->objects[1].intersect = intersect_sphere;

	static t_plane	plane1_shape;
	plane1_shape.normal = normalize((Vector){0, 1, 0});
	plane1_shape.point = (Vector){0, 0, 0};
	rt->objects[2].color = hex_to_rgb(0x0);
	rt->objects[2].smoothness = .95f;
	rt->objects[2].specular_prob = .5f;
	rt->objects[2].light_entensity = 0.f;
	rt->objects[2].shape = (void*)&plane1_shape;
	rt->objects[2].intersect = intersect_plane;
	rt->objects[2].normal = plane_normal;

	static t_sphere	light2_shape;
	light2_shape.center = (Vector){5, 5, -5};
	light2_shape.radius = 1.f;
	rt->objects[3].shape = (void*)&light2_shape;
	rt->objects[3].color = hex_to_rgb(0xFFFFFF);
	rt->objects[3].light_entensity = 2.f;
	rt->objects[3].intersect = intersect_sphere;

	rt->nb_objects = 4;
}

void    kernel(t_rt *rt)
{
	t_sphere	sphere4_shape;
	sphere4_shape.center = (Vector){-5, 3, -15};
	sphere4_shape.radius = 3.f;
	rt->objects[3].color = hex_to_rgb(0x8Fbcff);
	rt->objects[3].smoothness = 1.f;
	rt->objects[3].specular_prob = 0.5f;
	rt->objects[3].light_entensity = 0.f;
	rt->objects[3].shape = (void*)&sphere4_shape;
	rt->objects[3].intersect = intersect_sphere;
	rt->objects[3].normal = sphere_normal;

	t_plane	plane2_shape;
	plane2_shape.normal = normalize((Vector){1, 0, 0});
	plane2_shape.point = (Vector){-5, 0, 0};
	rt->objects[1].color = hex_to_rgb(0xff4040);
	rt->objects[1].smoothness = 0.f;
	rt->objects[1].specular_prob = 0.5f;
	rt->objects[1].light_entensity = 0.f;
	rt->objects[1].shape = (void*)&plane2_shape;
	rt->objects[1].intersect = intersect_plane;
	rt->objects[1].normal = plane_normal;

	t_plane	plane3_shape;
	plane3_shape.normal = normalize((Vector){-1, 0, 0});
	plane3_shape.point = (Vector){5, 0, 0};
	rt->objects[2].color = hex_to_rgb(0x5c40ff);
	rt->objects[2].smoothness = 0.f;
	rt->objects[2].specular_prob = 0.5f;
	rt->objects[2].light_entensity = 0.f;
	rt->objects[2].shape = (void*)&plane3_shape;
	rt->objects[2].intersect = intersect_plane;
	rt->objects[2].normal = plane_normal;

	t_plane	plane4_shape;
	plane4_shape.normal = normalize((Vector){0, 0, 1});
	plane4_shape.point = (Vector){0, 0, -20};
	rt->objects[3].color = hex_to_rgb(0xFFFFFF);
	rt->objects[3].smoothness = 0.f;
	rt->objects[3].specular_prob = 0.5f;
	rt->objects[3].light_entensity = 0.f;
	rt->objects[3].shape = (void*)&plane4_shape;
	rt->objects[3].intersect = intersect_plane;
	rt->objects[3].normal = plane_normal;

	t_plane	plane5_shape;
	plane5_shape.normal = normalize((Vector){0, -1, 0});
	plane5_shape.point = (Vector){0, 5, 0};
	rt->objects[4].smoothness = 0.f;
	rt->objects[4].specular_prob = 0.5f;
	rt->objects[4].color = (t_rgb){1, 1, 1};
	rt->objects[4].light_entensity = 0.f;
	rt->objects[4].shape = (void*)&plane5_shape;
	rt->objects[4].intersect = intersect_plane;
	rt->objects[4].normal = plane_normal;
}