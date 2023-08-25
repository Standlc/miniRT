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

#define WIDTH		1000
#define HEIGHT		550
#define RPP			500
#define CAM_FUZZ	1.0f
#define MAX_DEPTH	5
#define ON_DESTROY	17
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

enum event_hooks {
	KEY_PRESS = 2,
	KEY_UP = 3,
	MOUSE_DOWN = 4,
	MOUSE_UP = 5,
	MOUSE_MOVE = 6
};

enum event_mask {
	KEY_PRESS_MASK = 0,
	KEY_UP_MASK = 0,
	MOUSE_DOWN_MASK = 0,
	MOUSE_UP_MASK = 0,
	MOUSE_MOVE_MASK = 0
};

#else

#include <X11/keysym.h>
#include <X11/X.h>

enum events {
	LEFT_CLICK = 1,
	CONTROL = 65513,
	ESC = XK_Escape,
	PRINT = 112,
};

enum event_hooks {
	KEY_PRESS = KeyPress,
	KEY_UP = KeyRelease,
	MOUSE_DOWN = ButtonPress,
	MOUSE_UP = ButtonRelease,
	MOUSE_MOVE = MotionNotify
};

enum event_mask {
	KEY_PRESS_MASK = KeyPressMask,
	KEY_UP_MASK = KeyReleaseMask,
	MOUSE_DOWN_MASK = ButtonPressMask,
	MOUSE_UP_MASK = ButtonReleaseMask,
	MOUSE_MOVE_MASK = PointerMotionMask
};

#endif

#include "structures.h"
#include "rendering.h"
#include "parsing.h"

int		close_program(t_rt *data);
void	free_object(t_material *object);
void	free_elements(t_rt *rt);

#endif
