/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:59:24 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:41:30 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		d_with_zero_padding(t_list opt, long *ptr, int *print_len)
{
	int ret;

	ret = 0;
	if (opt.zero == 0)
		return (0);
	if (*ptr < 0)
	{
		if (*print_len > opt.width)
			ret = 1;
		else
			ret = 0;
		ft_putchar('-');
		ft_pad_left_zero(opt.width, *print_len, opt.left, opt.zero);
		*ptr = ft_abs(*ptr);
		*print_len = *print_len - 1;
	}
	else
		ft_pad_left_zero(opt.width, *print_len, opt.left, opt.zero);
	return (ret);
}

void	d_info_check(t_list *opt, long *ptr, int *print_len)
{
	if ((*opt).precision == 1 && *ptr == 0)
		*print_len = 0;
	if ((*opt).precs_star == 1 && (*opt).precs_len < 0 && *ptr == 0)
	{
		*ptr = 0;
		*print_len = 1;
	}
	if ((*opt).precision == 1 || (*opt).left == 1)
		(*opt).zero = 0;
	if ((*opt).zero_original == 1 && (*opt).precs_len < 0 &&
												(*opt).width_neg == 0)
		(*opt).zero = 1;
}

int		d_without_precision(t_list opt, long ptr, int print_len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (!(tmp = ft_itoa(ptr)))
		return (-1);
	if (opt.width < 0)
		opt.width = ft_abs(opt.width);
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

int		d_conversion(t_list opt, va_list *ap)
{
	int		ret;
	long	ptr;
	int		print_len;
	int		d_wo_precision;

	ret = 0;
	d_wo_precision = 0;
	ptr = (long)va_arg(*ap, int);
	print_len = ft_len(ptr);
	d_info_check(&opt, &ptr, &print_len);
	ret = d_with_zero_padding(opt, &ptr, &print_len);
	if (opt.precision == 1)
		ret += d_with_precision(opt, ptr, print_len);
	else
	{
		d_wo_precision = d_without_precision(opt, ptr, print_len);
		if (d_wo_precision == -1)
			return (-1);
		else
			ret += d_wo_precision;
	}
	return (ret);
}
