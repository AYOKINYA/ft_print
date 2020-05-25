/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_low_x_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:37:44 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:07 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	low_x_with_precision(t_list opt, unsigned int ptr, int print_len)
{
	int ret;

	ret = 0;
	opt.zero = 0;
	if (opt.zero_original == 1 && opt.precs_len < 0 && opt.width_neg == 0)
		opt.zero = 1;
	ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	if (print_len > opt.precs_len)
		ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	else
		ft_pad_left_blnk(opt.width, opt.precs_len, opt.left, opt.zero);
	ft_pad_left_zero(opt.precs_len, print_len, 0, 1);
	if (opt.precs_len != 0 || ptr != 0)
		ft_putnbr_base(ptr, "0123456789abcdef");
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

int	low_x_without_precision(t_list opt, unsigned int ptr, int print_len)
{
	int ret;

	ret = 0;
	ft_pad_left_zero(opt.width, print_len, opt.left, opt.zero);
	ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	ft_putnbr_base(ptr, "0123456789abcdef");
	ft_pad_right_blnk(opt.width, print_len, opt.left);
	if (opt.width > print_len)
		ret = opt.width;
	else
		ret = print_len;
	return (ret);
}

int	low_x_conversion(t_list opt, va_list *ap)
{
	int				ret;
	unsigned int	ptr;
	int				print_len;

	ret = 0;
	ptr = va_arg(*ap, int);
	print_len = ft_converted_len(ptr, "0123456789abcdef");
	if (opt.precision == 1 && opt.precs_len == 0 && ptr == 0)
		print_len = 0;
	if (opt.precision == 1)
		ret = low_x_with_precision(opt, ptr, print_len);
	else
		ret = low_x_without_precision(opt, ptr, print_len);
	return (ret);
}
