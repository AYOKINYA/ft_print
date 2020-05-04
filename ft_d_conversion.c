#include "ft_print.h"

int	d_with_zero_padding(t_list opt, int *ptr, int print_len)
{
	int ret;

	ret = 0;
	if (opt.zero == 0)
		return (0);
	if (*ptr < 0)
	{
		ret = 1;
		ft_putchar('-');
		ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
		*ptr = ft_abs(*ptr);
	}
	else
		ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	return (ret);
}

int	d_conversion(t_list opt, va_list *ap)
{
	int ret;
	int ptr;
	int print_len;
	int d_wo_precision;

	ret = 0;
	d_wo_precision = 0;
	if (!(ptr = va_arg(*ap, int)))
		return (-1);
	print_len = ft_len(ptr);
	if (opt.precision == 1)
		opt.zero = 0;
	ret = d_with_zero_padding(opt, &ptr, print_len);
	if (opt.precision == 1)
		ret = d_with_precision(opt, ptr, print_len);
	else
	{
		d_wo_precision = d_without_precision(opt, ptr, print_len);
		if ( d_wo_precision == -1)
			return (-1);
		else
			ret += d_wo_precision;
	}
	return (ret);
}