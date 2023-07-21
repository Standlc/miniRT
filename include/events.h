#ifndef EVENTS_H
# define EVENTS_H

#ifdef __APPLE__

enum events {
	RIGHT_CLICK = 1,
	CONTROL = 259,
	ESC = 53,
	PRINT = 35,
};

#else

enum events {
	RIGHT_CLICK = 1,
	CONTROL = 259,
	ESC = 53,
};

#endif

#endif