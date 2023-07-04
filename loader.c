#include "miniRT.h"

# define LOADING_SYMBOLS	"\\|/-"

void	loader(int frequency)
{
	static int	i = 0;

	if (i % frequency == 0)
	{
		write(1, "[", 1);
		write(1, &(LOADING_SYMBOLS[i % 4]), 1);
		write(1, "]", 1);
		write (1, "\b\b\b", 3);
	}
	i++;
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			ft_putchar_fd('-', fd);
		}
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else
			ft_putchar_fd(n + '0', fd);
	}
}

void	loading_bar(int max, float curr)
{
	int		i;
	float	progress;

	progress = curr / max * 50;
	i = 0;
	write(1, "\33[2K\r", 6);
	write(1, "[", 1);
	i = 1;
	while (i < progress)
	{
		write(1, "#", 1);
		i++;
	}
	while (i < 50)
	{
		write(1, " ", 1);
		i++;
	}
	write(1, "] ", 2);
	ft_putnbr_fd(curr / max * 100.0f, 1);
	write(1, "% ", 2);
	write(1, "[frame: ", 9);
	ft_putnbr_fd(curr, 1);
	write(1, "]", 2);
}