#include "minirt.h"

t_system	create_system(t_vec up)
{
	t_system	system;
 
	up = normalize(up);
	system.y = up;
	if (fabs(dot((t_vec){0, 0, 1}, up)) < 1)
		system.x = cross_product(up, (t_vec){0, 0, 1});
	else
		system.x = cross_product(up, (t_vec){0, 1, 0});

	system.z = cross_product(system.x, system.y);
	return (system);
}