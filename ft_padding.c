#include "ft_print.h"

void	ft_pad_right_blnk(int width, int print_len, int left)
{
	if (width > print_len && left == 1)
	{
		while(width != print_len)
		{
			ft_putchar(' ');
			--width;
		}
	}
}


void	ft_pad_left_blnk(int width, int print_len, int left, int zero)
{
	if (width > print_len && left != 1 && zero != 1)
	{
		while(width != print_len)
		{
			ft_putchar(' ');
			--width;
		}
	}
}

void	ft_pad_left_zero(int width, int print_len , int left, int zero)
{
	if (width > print_len && left != 1 && zero == 1)
	{
		while(width != print_len)
		{
			ft_putchar('0');
			--width;
		}
	}
}

int		ft_max(int width, int precs_len)
{
	if (width >= precs_len)
		return (width);
	else
		return (precs_len);
}