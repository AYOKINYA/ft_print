#include "ft_print.h"

int	ft_print_till_percent(const char **format)
{
	int ret;

	ret = 0;
	while ((*format) != ft_strchr(*format, '%'))
	{
		write(1, *format, 1);
		++(*format);
		++ret;
	}
	++(*format);
	return (ret);
}

void	ft_left_n_zeroflag(const char **format, t_list *opt)
{
	if (**format == '-')
		{
			(*opt).left = 1;
			++(*format);
		}
		if (**format == '0')
		{
			(*opt).zero = 1;
			++(*format);
		}
		if (**format == '-' && **(format - 2) != '-')
		{
			(*opt).left = 1;
			++(*format);
		}
}

void	ft_read_width(const char **format, t_list *opt, va_list *ap)
{
	if ((**format >= '1' && **format <= '9') || **format == '*')
	{
		if (**format == '*')
		{
			(*opt).width = va_arg(*ap, int);
			if ((*opt).width < 0)
			{
				(*opt).width = ft_abs((*opt).width);
				(*opt).left = 1;
			}
			++(*format);
		}
		else
		{
			(*opt).width = ft_atoi(*format);
			while(ft_is_numeric(**format))
				++(*format);
		}
	}
}
void	ft_read_precision(const char **format, t_list *opt, va_list *ap)
{
	if (**format == '.')
	{
		(*opt).precision = 1;
		++(*format);
	}
	if ((**format >= '0' && **format <= '9') || **format == '*')
	{
		if (**format == '*')
		{
			(*opt).precs_len = va_arg(*ap, int);
			++(*format);
		}
		else
		{
			(*opt).precs_len = ft_atoi(*format);
			while (ft_is_numeric(**format))
				++(*format);
		}
	}
}