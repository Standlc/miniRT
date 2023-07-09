LIBC = 	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_tolower.c ft_toupper.c ft_split.c ft_itoa.c ft_strjoin.c ft_substr.c ft_strtrim.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c

LIBCH = libft.h

HEADERS_LIBC = ${addprefix includes/libc/, ${LIBCH}}

PTF =	ft_printf.c ft_put_str_char.c ft_address_hex.c ft_nbr.c ft_what.c ft_minimum_field_width.c \
		ft_fonctions_bonus.c ft_minus.c ft_check_first_flags.c

PTFH =	ft_printf.h

HEADERS_PTF = ${addprefix includes/ptf/, ${PTFH}}

GNL =	get_next_line.c get_next_line_utils.c

GNLH =	get_next_line.h

HEADERS_GNL = ${addprefix includes/gnl/, ${GNLH}}

FILES = ${addprefix libc/, ${LIBC}} \
		${addprefix gnl/, ${GNL}} \
		${addprefix ptf/, ${PTF}}

SRCS =	${addprefix srcs/, ${FILES}} 

OBJ = ${addprefix binaries/, ${FILES}}

OBJS = ${OBJ:%.c=%.o}

NAME = libft.a

LIB = ar rcs

CC 	= cc

RM 	= rm -f

CFLAGS = -Wall -Wextra -Werror

binaries/libc/%.o: srcs/libc/%.c ${HEADERS_LIBC} | binaries/libc
	${CC} ${CFLAGS} -I./includes/libc/ -c $< -o $@

binaries/gnl/%.o: srcs/gnl/%.c ${HEADERS_GNL} | binaries/gnl
	${CC} ${CFLAGS} -I./includes/gnl/ -c $< -o $@

binaries/ptf/%.o: srcs/ptf/%.c ${HEADERS_PTF} | binaries/ptf
	${CC} ${CFLAGS} -I./includes/ptf/ -c $< -o $@

${NAME}: ${OBJS}
	${LIB} ${NAME} ${OBJS}

all: ${NAME}

binaries/ptf :
	@mkdir -p binaries/ptf

binaries/gnl :
	@mkdir -p binaries/gnl

binaries/libc :
	@mkdir -p binaries/libc

clean:
	${RM} -r binaries

fclean: clean
	 ${RM} ${NAME}

re: fclean all

.PHONY:	all bonus clean fclean re
