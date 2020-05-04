#include "ft_print.h"

int	d_negative_print(t_list opt, int *ptr, int *print_len)
{
	int		ret;
	char	*tmp;
	
	ret = 0;
	if (opt.precs_len >= opt.width)
		ret = 1;
	ft_putchar('-');
	*ptr = ft_abs(*ptr);
	*print_len = ft_len(*ptr);
	if (!(tmp = ft_itoa(*ptr)))
		return (-1);
	ft_pad_left_zero(opt.precs_len, *print_len, 0, 1);
	write(1, tmp, *print_len);
	*print_len = ft_len(*ptr) + 1;
	free(tmp);
	return (ret);
}

int	d_positive_print(t_list opt, int ptr, int print_len)
{
	char	*tmp;

	if (!(tmp = ft_itoa(ptr)))
		return (-1);
	ft_pad_left_zero(opt.precs_len, print_len, 0, 1);
	write(1, tmp, print_len);
	free(tmp);
	return (0);
}

void	ft_d_conversion_pad_right_blnk(t_list opt, int print_len)
{
	if (print_len > opt.precs_len)
		ft_pad_right_blnk(opt.width, print_len, opt.left);
	else
		ft_pad_right_blnk(opt.width, opt.precs_len + 1, opt.left);
}

int	d_with_precision(t_list opt, int ptr, int print_len)
{
	int	ret;

	ret = 0;
	if (print_len > opt.precs_len)
		ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	else
	{   if (ptr < 0)
			ft_pad_left_blnk(opt.width, opt.precs_len + 1, opt.left, opt.zero);
		else
			ft_pad_left_blnk(opt.width, opt.precs_len, opt.left, opt.zero);
	}
	if (ptr < 0)
		ret = d_negative_print(opt, &ptr, &print_len);
	else
		ret = d_positive_print(opt, ptr, print_len);
	if (ret == -1)
		return (-1);
	ft_d_conversion_pad_right_blnk(opt, print_len);
	if (opt.width > print_len || opt.precs_len > print_len)
		ret += ft_max(opt.width, opt.precs_len);
	else
		ret = print_len;
	return (ret);
}

int	d_without_precision(t_list opt, int ptr, int print_len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (!(tmp = ft_itoa(ptr)))
		return (-1);
	ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	write(1, tmp, print_len);
	ft_pad_right_blnk(opt.width, print_len, opt.left);
	free(tmp);
	if (opt.width > print_len)
		ret = opt.width;
	else
		ret = print_len;
	return (ret);
}