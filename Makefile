NAME		=	miniRT

NAME_L		=	miniRT_L

SRCS		=	main.c						rendering/render.c\
				rendering/utils/vector.c	\
				rendering/events/utils.c				rendering/utils/colors.c	\
				rendering/utils/utils.c				rendering/utils/loader.c	\
				rendering/shapes/sphere.c				rendering/shapes/plane.c		\
				rendering/shapes/cylinder.c 			rendering/shapes/circle.c \
				rendering/shapes/cone.c 				\
				rendering/shading/bump_mapping.c 		\
				rendering/events/events.c  rendering/events/mouse_events.c \
				rendering/utils/coordinate_system.c \
				rendering/shading/procedural_texturing.c rendering/utils/random.c\
				rendering/shapes/rectangle.c	\
				rendering/shading/shading.c			rendering/shading/direct_light_sampling.c \
				parsing/parse_normal_map.c	\
				parsing/parsing.c	\
				parsing/utils/error_message.c	parsing/utils/fonction_utils.c \
				parsing/input/get_content.c		parsing/input/check_input.c\
				parsing/type/type_unique.c		parsing/type/type.c	\
				parsing/type/check_syntax/other.c parsing/type/check_syntax/range.c \
				parsing/type/check_syntax/rgb.c \
				parsing/type/check_syntax/vector.c parsing/type/check_syntax/letter.c\
				parsing/fill_rt/fill_rt.c \
				parsing/fill_rt/materials/fill_data.c	parsing/fill_rt/materials/fill_materials.c \
				parsing/fill_rt/get_number/conversion.c parsing/fill_rt/get_number/get_value.c\

OBJS		=	$(SRCS:.c=.o)

LIB			=	libft.a

LIBFT		=	Libft

CC			=	cc

CFLAGS		=	-Wall -Wextra #-Werror

INC_LIB		=	-ILibft/includes/libc -ILibft/includes/gnl -Iinclude

#LINUX
INCLUDES_L	=	-Imlx $(INC_LIB)
MINILIBX_L	=	mlx
XFLAGS_L	=	-lmlx -lXext -lX11

#MACOS
INCLUDES	=	-Iminilibx_macos $(INC_LIB)
MINILIBX	=	minilibx_macos
XFLAGS		=	-lmlx -framework OpenGL -framework AppKit

MATH_LIB	=	-lm

RM			=	rm -f

all : libs $(NAME)

linux : libs-l ${NAME_L}

${NAME_L} : ${OBJS}
	${CC} ${OBJS} -LLibft -lft -Lmlx -lmlx -lX11 -lXext -lm -o ${NAME_L}

$(NAME) : $(OBJS) include/minirt.h
		$(CC) $(OBJS) -LLibft -lft -L$(MINILIBX) $(XFLAGS) $(MATH_LIB) -o $(NAME)

%.o : %.c Makefile
		$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_L) -c $< -o $@

libs:
		@$(MAKE) -C $(MINILIBX)
		@$(MAKE) -C Libft

libs-l:
		@$(MAKE) -C $(MINILIBX_L)
		@$(MAKE) -C Libft

clean:
		@$(RM) $(OBJS)
		@$(MAKE) clean -C $(MINILIBX)
		@$(MAKE) clean -C $(MINILIBX_L)
		@$(MAKE) clean -C Libft

fclean:	clean
		@$(RM) $(NAME)
		@$(RM) $(NAME_L)
		@$(MAKE) fclean -C Libft

re:		fclean all

.PHONY: all libs clean fclean re
