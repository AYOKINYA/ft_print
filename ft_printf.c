/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:51:55 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:21 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int		ret;
	int		each_ret;

	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (ft_strchr(format, '%'))
		{
			each_ret = ft_process_formatting(&format, &ap);
			if (each_ret == -1)
				return (-1);
			else
				ret += each_ret;
		}
		else
		{
			ret += ft_putstr(format);
			break ;
		}
	}
	va_end(ap);
	return (ret);
}
