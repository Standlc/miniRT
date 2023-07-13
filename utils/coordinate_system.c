#include "minirt.h"

t_space	create_system(t_vec ref)
{
	t_space	system;
 
	system.y = ref;
	if (fabs(dot((t_vec){0, 0, -1}, ref)) < 1)
		system.x = cross_product((t_vec){0, 0, -1}, ref);
	else if (fabs(dot((t_vec){0, 1, 0}, ref)) < 1)
		system.x = cross_product((t_vec){0, 1, 0}, ref);
	else if (fabs(dot((t_vec){1, 0, 0}, ref)) < 1)
		system.x = cross_product((t_vec){1, 0, 0}, ref);

	system.z = cross_product(system.y, system.x);
	return (system);
}