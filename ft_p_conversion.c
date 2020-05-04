#include "ft_print.h"

int	p_with_precision(t_list opt, char *ptr, int print_len)
{
	int ret;

	ret = 0;
	if (opt.precs_len <= print_len - 2)
		ft_pad_left_blnk(opt.width, print_len, 0, 0); 
		
	else
		ft_pad_left_blnk(opt.width, opt.precs_len + 2, 0, 0);
	write(1, "0x", 2);
	if ((opt.precs_len > print_len - 2))
		ft_pad_left_zero(opt.precs_len, print_len - 2, 0, 1);
	ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	if (opt.precs_len == 0)
		ft_pad_right_blnk(opt.width, print_len, opt.left);
	if (opt.width > print_len || opt.precs_len > print_len)
	{
		if (opt.width - opt.precs_len == 1)
			ret = 1;
		if (opt.width <= opt.precs_len)
			ret = 2;
		ret += ft_max(opt.width, opt.precs_len);
	}
	else
		ret = print_len;
	return (ret);
}

int	p_without_precision(t_list opt, char *ptr, int print_len)
{
	int ret;

	ret = 0;
	ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	write(1, "0x", 2);
	ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	ft_pad_right_blnk(opt.width, print_len, opt.left);
	if (opt.width > print_len)
		ret = opt.width;
	else
		ret = print_len;
	return (ret);
}

int	p_conversion(t_list opt, va_list *ap)
{
	int		ret;
	char	*ptr;
	int		print_len;

	ret = 0;
	if (!(ptr = va_arg(*ap, char*)))
		return (-1);
	print_len = ft_len((unsigned long long)ptr) - 1;
	if (opt.precision == 1)
		ret = p_with_precision(opt, ptr, print_len);
	else
		ret = p_without_precision(opt, ptr, print_len);
	return (ret);
}