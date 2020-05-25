/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:47:52 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:17 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pad_right_blnk(int width, int print_len, int left)
{
	if (width > print_len && left == 1)
	{
		while (width != print_len)
		{
			ft_putchar(' ');
			--width;
		}
	}
}

void	ft_pad_left_blnk(int width, int print_len, int left, int zero)
{
	if (width > print_len && left != 1 && zero != 1)
	{
		while (width != print_len)
		{
			ft_putchar(' ');
			--width;
		}
	}
}

void	ft_pad_left_zero(int width, int print_len, int left, int zero)
{
	if (width > print_len && left != 1 && zero == 1)
	{
		while (width != print_len)
		{
			ft_putchar('0');
			--width;
		}
	}
}

int		ft_max(int width, int precs_len)
{
	if (width >= precs_len)
		return (width);
	else
		return (precs_len);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	i = 0;
	u_s1 = (unsigned char*)s1;
	u_s2 = (unsigned char*)s2;
	while (u_s1[i] != '\0' && u_s2[i] != '\0')
	{
		if (u_s1[i] != u_s2[i])
			return ((u_s1[i] - u_s2[i]));
		else
			++i;
	}
	return (u_s1[i] - u_s2[i]);
}
