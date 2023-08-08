#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"

#define WIDTH       1000
#define HEIGHT      550
#define RPP			500
#define CAM_FUZZ	1.0f
#define MAX_DEPTH	5
#define ON_DESTROY  17
#define NB_MAP		5

enum textures {
	CHECKERS = 1,
	BUMP_MAP = 2,
};

enum {
	AMBIENT = 1,
	CAMERA = 2,
	LIGHT = 3,
	SPHERE = 4,
	PLAN = 5,
	CYLINDER = 6,
	CONE = 7,
};

#ifdef __APPLE__

enum events {
	LEFT_CLICK = 1,
	CONTROL = 259,
	ESC = 53,
	PRINT = 35,
};

#else

enum events {
	LEFT_CLICK = XK_Right,
	CONTROL = XK_Alt_R,
	ESC = XK_Escape,
	PRINT = 35,
};

#endif

#include "structures.h"
#include "rendering.h"
#include "parsing.h"

#endif