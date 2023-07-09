/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 05:31:36 by svan-de-          #+#    #+#             */
/*   Updated: 2022/12/16 20:36:22 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_index{
	int		i;
	int		option;
	int		flag;
	int		len;
	int		flag2;
	size_t	p_arg;
	ssize_t	arg;
	char	*str_arg;
}	t_index;

typedef struct s_len{
	int	number_of;
	int	write;
	int	len_arg;
}	t_len;

void	ft_is_percent(char *str, t_index *index);

void	ft_first_f(char *str, t_index *index);

int		ft_check_zero(char *str, t_index *index);

size_t	ft_len_hex(size_t number, t_index *index);

void	ft_unsigned_hex(char *str, unsigned int number, char c, t_index *index);

void	ft_hexadecimal(size_t number_address, int *index_option);

int		ft_address(size_t number_address);

void	ft_go_back(char *str, t_index *index);

int		ft_sharp(char *str, t_index *index);

int		ft_plus_space(char *str, t_index *index, int f);

void	ft_zero(char *str, t_index *index);

void	ft_precision(char *str, t_index *index);

int		ft_check_sign(int j, char *str);

void	ft_precision_f2(t_index *index, t_len *len);

void	ft_check_flag2(char *str, t_index *index);

void	ft_check_prec(char *str, t_index *index, t_len *len);

void	ft_minus(char *str, t_index *index);

void	ft_putnbr_pf(long nb, t_index *index);

void	ft_putnbr_u(unsigned int nb, t_index *index);

int		ft_atoi_pf(char *str, t_index *index);

int		ft_is_sharp(t_index *index, char *str, char c);

void	ft_set_flag(t_index *index);

int		ft_putchar_pf(char c);

int		ft_putstr_pf(char *str);

int		ft_strlen_pf(char *str);

char	ft_what_arg(char *str);

int		ft_pre(char *str, t_index *index, int f);

int		ft_what_x(char *str, int i);

void	ft_for_hex(char *str, char c, t_index *index);

int		ft_is_printf_char(char c);

int		ft_was_option(char *str, t_index *index);

int		ft_len_arg(char *str, t_index *index);

char	*ft_strdup_pf(const char *src);

void	ft_print_number_of(t_index *index, t_len *len, int f);

void	ft_got_len(char *str, t_index *index, t_len *len);

void	ft_check_precision(char *str, t_index *index, t_len *len);

void	ft_number(char *str, t_index *index);

int		ft_next_char(char *str, t_index *index);

int		ft_check_flags(char *str, t_index *index);

int		ft_next_arg(char *str, va_list args, t_index *index);

void	ft_symbol(char *str, va_list args, t_index *index);

int		ft_printf(const char *str, ...)__attribute__ ((format (printf, 1, 2)));

#endif
