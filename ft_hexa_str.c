/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:35:54 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:39:04 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putnbr_base(unsigned long long nb, const char *base)
{
	unsigned long long	base_len;

	base_len = ft_strlen(base);
	if (nb < base_len)
		ft_putchar(base[nb]);
	else
	{
		ft_putnbr_base(nb / base_len, base);
		ft_putchar(base[nb % base_len]);
	}
}

int			ft_converted_len(unsigned long long nb, const char *base)
{
	unsigned long long	base_len;
	int					count;

	base_len = ft_strlen(base);
	count = 0;
	if (nb < base_len)
		++count;
	else
	{
		while (nb != 0)
		{
			nb = nb / base_len;
			++count;
		}
	}
	return (count);
}

long long	ft_abs(long long n)
{
	if (n < 0)
		n = n * -1;
	return (n);
}

int			ft_len(long long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		++len;
	while (n != 0)
	{
		n = n / 10;
		++len;
	}
	return (len);
}

char		*ft_itoa(long long n)
{
	char		*res;
	int			len;
	long		nbr;

	nbr = n;
	len = ft_len(nbr);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	res[len] = '\0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = ft_abs(nbr);
	}
	if (nbr == 0)
		res[0] = '0';
	while (nbr != 0)
	{
		--len;
		res[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (res);
}
