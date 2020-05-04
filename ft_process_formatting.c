#include "ft_print.h"

int	ft_type_conversion(const char **format, t_list opt, va_list *ap)
{
	int ret;
	
	ret = 0;
	if (**format == 'c')
		ret = c_conversion(opt, ap);
	else if (**format == 's')
		ret = s_conversion(opt, ap);
	else if (**format == 'p')
		ret = p_conversion(opt, ap);
	else if (**format == 'd' || **format == 'i')
		ret = d_conversion(opt, ap);
	else if (**format == 'u')
		ret = u_conversion(opt, ap);
	else if (**format == 'x')
		ret = low_x_conversion(opt, ap);
	else if (**format == 'X')
		ret = cap_x_conversion(opt, ap);
	else if (**format == '%')
		ret = percent_conversion(opt);
	return (ret);
}

int	ft_process_formatting(const char **format, va_list *ap)
{
	int		ret;
	int		type_conversion;
	t_list	opt;
	
	ret = 0;
	type_conversion = 0;
	opt.width = 0;
	opt.left = 0;
	opt.zero = 0;
	opt.precision = 0;
	opt.precs_len = 0;
	ret += ft_print_till_percent(format);
	ft_left_n_zeroflag(format, &opt);
	ft_read_width(format, &opt, ap);
	ft_read_precision(format, &opt, ap);
	type_conversion = ft_type_conversion(format, opt, ap);
	if (type_conversion == -1)
		return (-1);
	ret += type_conversion;
	++(*format);
	return (ret);	
}