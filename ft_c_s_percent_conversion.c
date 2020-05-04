#include "ft_print.h"

int	c_conversion(t_list opt, va_list *ap)
{
	int ret;
	int ptr;
				
	ret = 0;
	if (!(ptr = va_arg(*ap, int)))
		return (-1);
	ft_pad_left_blnk(opt.width, 1, opt.left, opt.zero);
	ft_putchar(ptr);
	ft_pad_right_blnk(opt.width, 1, opt.left);
	if (opt.width > 1)
		ret = opt.width;
	else
		ret = 1;
	return (ret);
}

int	s_conversion(t_list opt, va_list *ap)
{
	char	*ptr;
	int		print_len;

	if (!(ptr = va_arg(*ap, char*)))
		ptr = "(null)";
	print_len = ft_strlen(ptr);
	if (opt.precision == 1 && opt.precs_len >= 0)
	{
		if (print_len >= opt.precs_len)
			print_len = opt.precs_len;
	}
	ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	write(1, ptr, print_len);
	ft_pad_right_blnk(opt.width, print_len, opt.left);
	if (opt.width > print_len)
		return (opt.width);
	else
		return (print_len);
}

int percent_conversion(t_list opt)
{
	int ret;
				
	ret = 0;
	ft_pad_left_blnk(opt.width, 1, opt.left, opt.zero);
	ft_putchar('%');
	ft_pad_right_blnk(opt.width, 1, opt.left);
	if (opt.width > 1)
		ret = opt.width;
	else
		ret = 1;
	return (ret);
}