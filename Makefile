NAME		=	miniRT

NAME-L		=	miniRT

SRCS		=	main.c						utils/vector.c	\
				camera/libx.c				utils/colors.c	\
				utils/utils.c				utils/loader.c	\
				shapes/sphere.c				shapes/plane.c		\
				scenes.c					shapes/rectangle.c	\

OBJS		=	$(SRCS:.c=.o)

#LIB			=	libft.a

#LIBFT		=	libft

CC			=	cc

CFLAGS		=	-Wall -Wextra #-Werror

#LINUX
INCLUDES-L	=	-Imlx -Ilibft
MINILIBX-L	=	mlx
XFLAGS-L	=	-lmlx -lXext -lX11

#MACOS
INCLUDES	=	-Iminilibx_macos
MINILIBX	=	minilibx_macos
XFLAGS		=	-lmlx -framework OpenGL -framework AppKit

MATH_LIB	=	-lm

RM			=	rm -f

all : libs $(NAME)

linux : libs-l ${NAME-L}

$(NAME) : miniRT.h $(OBJS)
		$(CC) $(OBJS) -L$(MINILIBX) $(XFLAGS) $(MATH_LIB) -o $(NAME)

${NAME-L} : ${OBJS}
	${CC} ${OBJS} -Lmlx -lmlx -lX11 -lXext -lm -o ${NAME-L}

%.o : %.c Makefile
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
		@$(MAKE) -C $(MINILIBX)

libs-l:
		@$(MAKE) -C $(MINILIBX-L)

clean:
		@$(RM) $(OBJS)
		@$(MAKE) clean -C $(MINILIBX)
		@$(MAKE) clean -C $(MINILIBX-L)

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) clean -C $(MINILIBX)
		@$(MAKE) clean -C $(MINILIBX-L)

re:		fclean all

.PHONY: all libs clean fclean re
