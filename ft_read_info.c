/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:54:10 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:36 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_till_percent(const char **format)
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
	while (**format == '-' || **format == '0')
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
				(*opt).width_neg = 1;
				(*opt).width = ft_abs((*opt).width);
				(*opt).left = 1;
				(*opt).zero = 0;
			}
			else
				(*opt).zero_original = (*opt).zero;
			++(*format);
		}
		else
		{
			(*opt).width = ft_atoi(*format);
			while (ft_is_numeric(**format))
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
			(*opt).precs_star = 1;
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
