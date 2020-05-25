/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:38:44 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 18:03:58 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*temp;

	len = 0;
	while (s[len] != '\0')
		++len;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		temp[i] = s[i];
		++i;
	}
	temp[i] = '\0';
	return (temp);
}

void	p_with_precision_body(t_list opt, unsigned long ptr, int *print_len,
																char *str)
{
	if (opt.precs_len < *print_len - 2)
		ft_pad_left_blnk(opt.width, *print_len - 2, 0, 0);
	else
		ft_pad_left_blnk(opt.width, opt.precs_len + 2, 0, 0);
	if (ft_strcmp(str, "0x0") == 0)
		write(1, "0x", 2);
	if ((opt.precs_len > *print_len - 2))
		ft_pad_left_zero(opt.precs_len, *print_len - 2, 0, 1);
	if (ft_strcmp(str, "0x0") != 0)
		ft_putnbr_base(ptr, "0123456789abcdef");
	if (opt.precs_len == 0)
		ft_pad_right_blnk(opt.width, *print_len, opt.left);
}

int		p_with_precision(t_list opt, unsigned long ptr, int *print_len,
																char *str)
{
	int ret;

	ret = 0;
	if (ft_strcmp(str, "0x0") == 0)
		*print_len = 2;
	p_with_precision_body(opt, ptr, print_len, str);
	if (opt.width > *print_len || opt.precs_len > *print_len)
	{
		if (opt.width - opt.precs_len == 1)
			ret = 1;
		if (opt.width <= opt.precs_len)
			ret = 2;
		ret += ft_max(opt.width, opt.precs_len);
	}
	else
		ret = *print_len;
	return (ret);
}

int		p_without_precision(t_list opt, unsigned long ptr, int print_len,
																	char *str)
{
	int ret;

	ret = 0;
	if (ft_strcmp(str, "0x0") != 0)
	{
		ft_pad_left_blnk(opt.width, print_len + 2, opt.left, opt.zero);
		write(1, "0x", 2);
		ft_putnbr_base(ptr, "0123456789abcdef");
		ft_pad_right_blnk(opt.width, print_len + 2, opt.left);
	}
	else
	{
		ft_pad_left_blnk(opt.width, 3, opt.left, opt.zero);
		write(1, "0x0", 3);
		ft_pad_right_blnk(opt.width, print_len, opt.left);
	}
	if (opt.width >= print_len + 2)
		ret = opt.width;
	else if (ft_strcmp(str, "0x0") == 0)
		ret = 3;
	else
		ret = print_len + 2;
	return (ret);
}

int		p_conversion(t_list opt, va_list *ap)
{
	int				ret;
	unsigned long	ptr;
	char			*str;
	int				print_len;

	ret = 0;
	if (!(ptr = (unsigned long)va_arg(*ap, unsigned long)))
	{
		if (!(str = ft_strdup("0x0")))
			return (-1);
		print_len = ft_strlen(str);
	}
	else
	{
		if (!(str = ft_strdup("X")))
			return (-1);
		print_len = ft_converted_len(ptr, "0123456789abcdef");
	}
	if (opt.precision == 1 && opt.precs_len == 0)
		ret = p_with_precision(opt, ptr, &print_len, str);
	else
		ret = p_without_precision(opt, ptr, print_len, str);
	free(str);
	return (ret);
}
