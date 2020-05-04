#include "ft_print.h"

int	u_with_precision(t_list opt, unsigned int ptr, int print_len)
{
	int	ret;
	
	opt.zero = 0;
	ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	if (print_len > opt.precs_len)
		ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	else
		ft_pad_left_blnk(opt.width, opt.precs_len, opt.left, opt.zero);
	ft_pad_left_zero(opt.precs_len, print_len, 0, 1);
	ft_putnbr(ptr);
	if (print_len > opt.precs_len)
		ft_pad_right_blnk(opt.width, print_len, opt.left);
	else
		ft_pad_right_blnk(opt.width, opt.precs_len, opt.left);
	if (opt.width > print_len || opt.precs_len > print_len)
		ret = ft_max(opt.width, opt.precs_len);
	else
		ret = print_len;
	return (ret);
}

int	u_without_precision(t_list opt, unsigned int ptr, int print_len)
{
	int	ret;
	
	ret = 0;
	ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	ft_putnbr(ptr);
	ft_pad_right_blnk(opt.width, print_len, opt.left);
	if (opt.width > print_len)
		ret = opt.width;
	else
		
		ret = print_len;
	return (ret);
}

int	u_conversion(t_list opt, va_list *ap)
{
	unsigned int	ptr;
	int				print_len;
	int				ret;

	ret = 0;
	if (!(ptr = va_arg(*ap, int)))
		return (-1);
	print_len = ft_len(ptr);
	if (opt.precision == 1)
		ret = u_with_precision(opt, ptr, print_len);
	else
		ret = u_without_precision(opt, ptr, print_len);
	return (ret);
}