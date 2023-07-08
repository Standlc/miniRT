NAME		=	miniRT

SRCS		=	main.c						utils/vector.c	\
				camera/libx.c				utils/colors.c	\
				utils/utils.c				utils/loader.c	\
				shapes/sphere.c				shapes/plane.c		\
				scenes.c					shapes/rectangle.c	\

OBJS		=	$(SRCS:.c=.o)

LIB			=	libft.a

LIBFT		=	libft

CC			=	cc

CFLAGS		=	-Wall -Wextra #-Werror

#LINUX
#INCLUDES	=	-Iminilibx-linux -Ilibft
#MINILIBX	=	minilibx-linux
#XFLAGS		=	-lmlx -lXext -lX11

#MACOS
INCLUDES	=	-Iminilibx_macos
MINILIBX	=	minilibx_macos
XFLAGS		=	-lmlx -framework OpenGL -framework AppKit

MATH_LIB	=	-lm

RM			=	rm -f

all : libs $(NAME)

$(NAME) : miniRT.h $(OBJS)
		$(CC) $(OBJS) -L$(MINILIBX) $(XFLAGS) $(MATH_LIB) -o $(NAME)

%.o : %.c Makefile
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
		@$(MAKE) -C $(MINILIBX)

clean:
		@$(RM) $(OBJS)
		@$(MAKE) clean -C $(MINILIBX)

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) clean -C $(MINILIBX)

re:		fclean all

.PHONY: all libs clean fclean re
