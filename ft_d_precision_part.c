/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_precision_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:08:37 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:00 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		d_negative_print(t_list opt, long *ptr, int *print_len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (opt.precs_len >= opt.width)
		ret = 1;
	ft_putchar('-');
	*ptr = ft_abs(*ptr);
	*print_len = ft_len(*ptr);
	if (!(tmp = ft_itoa(*ptr)))
		return (-1);
	ft_pad_left_zero(opt.precs_len, *print_len, 0, 1);
	write(1, tmp, *print_len);
	*print_len = ft_len(*ptr) + 1;
	free(tmp);
	*ptr = *ptr * -1;
	return (ret);
}

int		d_positive_print(t_list opt, long ptr, int print_len)
{
	char	*tmp;

	if (!(tmp = ft_itoa(ptr)))
		return (-1);
	ft_pad_left_zero(opt.precs_len, print_len, 0, 1);
	write(1, tmp, print_len);
	free(tmp);
	return (0);
}

void	ft_d_conversion_pad_right_blnk(t_list opt, long ptr, int print_len)
{
	if (print_len > opt.precs_len)
		ft_pad_right_blnk(opt.width, print_len, opt.left);
	else
	{
		if (ptr < 0)
			ft_pad_right_blnk(opt.width, opt.precs_len + 1, opt.left);
		else
			ft_pad_right_blnk(opt.width, opt.precs_len, opt.left);
	}
}

void	d_with_precision_pad_left_blnk(t_list opt, long ptr, int print_len)
{
	if (print_len > opt.precs_len)
		ft_pad_left_blnk(opt.width, print_len, opt.left, opt.zero);
	else
	{
		if (ptr < 0)
			ft_pad_left_blnk(opt.width, opt.precs_len + 1, opt.left, opt.zero);
		else
			ft_pad_left_blnk(opt.width, opt.precs_len, opt.left, opt.zero);
	}
}

int		d_with_precision(t_list opt, long ptr, int print_len)
{
	int	ret;

	ret = 0;
	d_with_precision_pad_left_blnk(opt, ptr, print_len);
	if (ptr < 0)
		ret = d_negative_print(opt, &ptr, &print_len);
	else
		ret = d_positive_print(opt, ptr, print_len);
	if (ret == -1)
		return (-1);
	ft_d_conversion_pad_right_blnk(opt, ptr, print_len);
	if (opt.width > print_len || opt.precs_len > print_len)
		ret += ft_max(opt.width, opt.precs_len);
	else if (ptr < 0 && (opt.precs_len + 1 > print_len))
		ret += print_len;
	else
		ret = print_len;
	return (ret);
}
