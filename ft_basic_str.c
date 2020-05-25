/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:51:43 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 00:41:09 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(const char *s)
{
	int count;

	count = 0;
	while (s[count] != '\0')
		++count;
	return (count);
}

void	ft_putchar(const char c)
{
	write(1, &c, 1);
}

int		ft_putstr(const char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		++i;
		++count;
	}
	return (count);
}

void	ft_putnbr(long long n)
{
	if (n >= 0 && n < 10)
		ft_putchar(n + '0');
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
	{
		if (n == -2147483648)
			write(1, "-2147483648", 11);
		else
		{
			ft_putchar('-');
			n = n * -1;
			ft_putnbr(n);
		}
	}
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}
