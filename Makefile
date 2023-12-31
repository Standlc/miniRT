NAME		=	miniRT

NAME_L		=	miniRT_L

SRCS		=	main.c									close_program.c \
				rendering/render.c						rendering/cast_ray.c \
				rendering/utils/ambient.c				rendering/utils/math.c \
				rendering/utils/vector.c				rendering/utils/colors.c \
				rendering/utils/loader.c				rendering/utils/random.c \
				rendering/utils/coordinate_system.c		rendering/utils/vector_methods.c \
				rendering/utils/vector_operations.c		\
				\
				rendering/shapes/cone/cone.c			rendering/shapes/cone/cone_intersection.c \
				rendering/shapes/cylinder/cylinder.c	rendering/shapes/cylinder/cylinder_intersection.c \
				rendering/shapes/cone/cone_texture.c	rendering/shapes/cylinder/cylinder_texture.c \
				rendering/shapes/sphere.c				rendering/shapes/plane.c \
				rendering/shapes/circle.c				\
				\
				rendering/shading/shading.c				rendering/shading/direct_light_sampling.c \
				rendering/shading/texture.c \
				\
				rendering/events/hooks.c				rendering/events/mouse_events.c \
				rendering/events/key_events.c			\
				\
				parsing/normal_map/parse_normal_map.c	\
				parsing/normal_map/fill_good_maps.c	\
				parsing/parsing.c	\
				parsing/utils/error_message.c	parsing/utils/fonction_utils.c \
				parsing/input/get_content.c		parsing/input/check_input.c\
				parsing/input/check_argument.c\
				parsing/type/type_unique.c		parsing/type/type.c	\
				parsing/type/check_syntax/other.c parsing/type/check_syntax/range.c \
				parsing/type/check_syntax/rgb.c parsing/type/check_syntax/null.c\
				parsing/type/check_syntax/vector.c parsing/type/check_syntax/letter.c\
				parsing/type/type_cylinder_cone_optionnal.c \
				parsing/fill_rt/fill_rt.c parsing/fill_rt/fill_rt_utils.c\
				parsing/fill_rt/materials/fill_data.c	parsing/fill_rt/materials/fill_materials.c \
				parsing/fill_rt/get_number/conversion.c parsing/fill_rt/get_number/get_value.c\

OBJS_DIR	=	$(addprefix binaries/, ${SRCS})

OBJS		=	$(OBJS_DIR:%.c=%.o)

LIB			=	libft.a

LIBFT		=	Libft

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

INC_LIB		=	-ILibft/includes/libc -ILibft/includes/gnl -Iincludes

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

MAKEFLAGS	+=	--no-print-directory

all : $(NAME) | libs

linux : ${NAME_L} | libs-l

binaries/%.o : %.c Makefile includes/minirt.h | binaries
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_L) -I./includes/ -c $< -o $@

${NAME_L} : ${OBJS} | libs-l
	@${CC} ${OBJS} -LLibft -lft -Lmlx -lmlx -lX11 -lXext -lm -o ${NAME_L}
	@echo "\033[32mminiRT compiled"

$(NAME) : $(OBJS) | libs
	@$(CC) $(OBJS) -LLibft -lft -L$(MINILIBX) $(XFLAGS) $(MATH_LIB) -o $(NAME)
	@echo "\033[32mminiRT compiled"


libs: minilibx_macos/libmlx.a Libft/libft.a

libs-l: mlx/libmlx.a Libft/libft.a

minilibx_macos/libmlx.a:
	@$(MAKE) -C $(MINILIBX) 2> /dev/null
	@echo "\033[32mmililibx compiled"

mlx/libmlx.a:
	@$(MAKE) -C $(MINILIBX_L)
	@echo "\033[32mmililibx compiled"

Libft/libft.a:
	@$(MAKE) -C Libft

binaries:
		@mkdir -p binaries

bonus: all

clean:
		@$(RM) -r binaries/
		@$(MAKE) clean -C $(MINILIBX)
		@$(MAKE) clean -C $(MINILIBX_L)
		@echo "\033[36mminilibx is clean"
		@$(MAKE) clean -C Libft
		@echo "\033[36mLibft is clean"
		@echo "\033[36mminiRT is clean"

fclean:	clean
		@$(RM) $(NAME)
		@$(RM) $(NAME_L)
		@$(MAKE) fclean -C Libft
		@echo "\033[36mminiRT file is delete"

re:		fclean all

.PHONY: all libs clean fclean re
