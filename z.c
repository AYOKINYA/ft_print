#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h> // va_start, va_arg, va_copy, va_end

typedef struct s_list
{
	int width;
	int left_align;
	int zero_padding;
	int precision;
	int precision_len;
	
}				t_list;

int     ft_strlen(const char *s)
{
    int count;

    count = 0;
    while (s[count] != '\0')
        ++count;
    return (count);
}

void    ft_putchar(const char c)
{
    write(1, &c, 1);
}

int	ft_putstr(const char *s)
{
    int i;
	int count;

    i = 0;
	count = 0;
    while(s[i] != '\0')
    {
        write(1, &s[i], 1);
        ++i;
		++count;
    }
	return (count);
}

char    *ft_strchr(const char *s, int c)
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

void	ft_putnbr_base(unsigned long long nb, const char *base)
{
	unsigned long long     base_len;

    base_len = ft_strlen(base);
    if (nb < base_len)
		ft_putchar(base[nb]);
	else
	{
		ft_putnbr_base(nb / base_len, base);
		ft_putchar(base[nb % base_len]);
	}
}

int     ft_converted_len(unsigned long long nb, const char *base)
{
	unsigned long long      base_len;
    int                     count;

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

long long   ft_abs(long long n)
{
    if (n < 0)
        n = n * -1;
    return (n);
}

long long   ft_len(long long n)
{
    int     len;

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

char        *ft_itoa(long long n)
{
    char    *res;
    long long     len;

    if (n == -2147483648)
        return ("-2147483648");
    len = ft_len(n);
    res = (char *)malloc(sizeof(char) * (len + 1));
    if (res == 0)
        return (0);
    res[len] = '\0';
    if (n < 0)
    {
        res[0] = '-';
        n = ft_abs(n);
    }
    if (n == 0)
        res[0] = '\0';
    while (n != 0)
    {
        --len;
        res[len] = n % 10 + '0';
        n = n / 10;
    }
    return (res);
}

int ft_is_space(const char c)
{
    if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
        return (1);
    return (0);
}

int ft_is_numeric(const char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_atoi(const char *str)
{
    int res;
    int i;
    int sign;

    res = 0;
    i = 0;
    sign = 1;
    while (str[i] != '\0' && ft_is_space(str[i]))
        ++i;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = sign * -1;
        ++i;
    }
    while(str[i] != '\0' && ft_is_numeric(str[i]))
    {
        res = res * 10 + (str[i] - 48);
        ++i;
    }
    return(sign * res);
}

void    ft_pad_right_blank(int width, int print_len, int left_align)
{
    if (width > print_len && left_align == 1)
    {
        while(width != print_len)
        {
            ft_putchar(' ');
            --width;
        }
    }
}

void    ft_pad_left_blank_char(int width, int print_len, int left_align)
{
    if (width > print_len && left_align != 1)
    {
        while(width != print_len)
        {
            ft_putchar(' ');
            --width;
        }
    }
}

void    ft_pad_left_blank(int width, int print_len, int left_align, int zero_padding)
{
    if (width > print_len && left_align != 1 && zero_padding != 1)
    {
        while(width != print_len)
        {
            ft_putchar(' ');
            --width;
        }
    }
}

void    ft_pad_left_zero(int width, int print_len , int left_align, int zero_padding)
{
    if (width > print_len && left_align != 1 && zero_padding == 1)
    {
        while(width != print_len)
        {
            ft_putchar('0');
            --width;
        }
    }
}

int		ft_max(int width, int precision_len)
{
	if (width >= precision_len)
		return (width);
	else
		return (precision_len);
}

int	c_conversion(t_list flag_n_val, va_list *ap)
{
	int ret;
	int ptr;
				
	ret = 0;
	ptr = va_arg(*ap, int);
	ft_pad_left_blank(flag_n_val.width, 1, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_zero(flag_n_val.width, 1, flag_n_val.left_align, flag_n_val.zero_padding);
    ft_putchar(ptr);
    ft_pad_right_blank(flag_n_val.width, 1, flag_n_val.left_align);
	if (flag_n_val.width > 1)
		ret = flag_n_val.width;
	else
		ret = 1;
	return (ret);
}

int	s_conversion(t_list flag_n_val, va_list *ap)
{
	char	*ptr;
	int     print_len;

	ptr = va_arg(*ap, char*);
	print_len = ft_strlen(ptr);
	if (flag_n_val.precision == 1)
	{
		if (print_len >= flag_n_val.precision_len)
			print_len = flag_n_val.precision_len;
	}
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	write(1, ptr, print_len);
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len)
		return (flag_n_val.width);
	else
		return (print_len);
}

int	p_with_precision(t_list flag_n_val, char *ptr, int print_len)
{
	int ret;

	ret = 0;
	if (flag_n_val.precision_len <= print_len - 2) //0x 제외
		ft_pad_left_blank(flag_n_val.width, print_len, 0, 0); // p를 수정해야 한다면 이 if & else문에서 ft_pad_right_blank를 추가해주면 된다.
		
	else
		ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len + 2, 0, 0);
	write(1, "0x", 2);
	if ((flag_n_val.precision_len > print_len - 2))
		ft_pad_left_zero(flag_n_val.precision_len, print_len - 2, 0, 1);
	ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	if (flag_n_val.precision_len == 0)
		ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	// left_blank가 width - (precision_len + 2)까지 밖에 안 채워져서 그 와 경우를 따로 고려해 더 해줘야 한다.
	if (flag_n_val.width > print_len || flag_n_val.precision_len > print_len)
	{
		if (flag_n_val.width - flag_n_val.precision_len == 1)
			ret = 1;
		if (flag_n_val.width <= flag_n_val.precision_len)
			ret = 2;
		ret += ft_max(flag_n_val.width, flag_n_val.precision_len);
	}
	else
		ret = print_len;
	return (ret);
}

int	p_without_precision(t_list flag_n_val, char *ptr, int print_len)
{
	int ret;

	ret = 0;
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	write(1, "0x", 2);
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len)
		ret = flag_n_val.width;
	else
		ret = print_len;
	return (ret);
}

int	p_conversion(t_list flag_n_val, va_list *ap)
{
	int		ret;
	char	*ptr;
	int     print_len;

	ret = 0;
	ptr = va_arg(*ap, char*);
	print_len = ft_len((unsigned long long)ptr) - 1;
	if (flag_n_val.precision == 1)
		ret = p_with_precision(flag_n_val, ptr, print_len);
	else
		ret = p_without_precision(flag_n_val, ptr, print_len);
	return (ret);
}

int	d_negative_print(t_list flag_n_val, int *ptr, int *print_len)
{
	int		ret;
	char	*tmp;
	
	ret = 0;
	if (flag_n_val.precision_len >= flag_n_val.width) // %10.10d이고 d=123일 때는 0000000123이다. 그러나 d가 음수로 -123이면 -0000000123이 된다. 앞에 마이너스 부호를 세준다.
		ret = 1;
	ft_putchar('-'); //zero padding이 있으면 음수가 제일 먼저 나와야 한다.
	*ptr = ft_abs(*ptr); //write할 때 필수로 ptr이 양수여야 한다.!!
	*print_len = ft_len(*ptr);
	tmp = ft_itoa(*ptr);
	ft_pad_left_zero(flag_n_val.precision_len, *print_len, 0, 1); // 0과 1을 직접 넣어준 이유는 ft_pad_left_zero를 사용하고자 하기 떄문이다.
	write(1, tmp, *print_len);
	*print_len = ft_len(*ptr) + 1;
	free(tmp);
	return (ret);
}

void	d_positive_print(t_list flag_n_val, int ptr, int print_len)
{
	char	*tmp;

	tmp = ft_itoa(ptr);
	ft_pad_left_zero(flag_n_val.precision_len, print_len, 0, 1);
	write(1, tmp, print_len);
	free(tmp);
}

int	d_with_precision(t_list flag_n_val, int ptr, int print_len)
{
	int	ret;

	ret = 0;
	if (print_len > flag_n_val.precision_len)
		ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	else
	{   if (ptr < 0)
			ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len + 1, flag_n_val.left_align, flag_n_val.zero_padding);
		else
			ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align, flag_n_val.zero_padding);
	}
	if (ptr < 0)
		ret = d_negative_print(flag_n_val, &ptr, &print_len);
	else
		d_positive_print(flag_n_val, ptr, print_len);
	if (print_len > flag_n_val.precision_len)
		ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	else
		ft_pad_right_blank(flag_n_val.width, flag_n_val.precision_len + 1, flag_n_val.left_align);
	if (flag_n_val.width > print_len || flag_n_val.precision_len > print_len)
		ret += ft_max(flag_n_val.width, flag_n_val.precision_len);
	else
		ret = print_len;
	return (ret);
}

int	d_without_precision(t_list flag_n_val, int ptr, int print_len)
{
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = ft_itoa(ptr);
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	write(1, tmp, print_len);
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	free(tmp);
	if (flag_n_val.width > print_len)
		ret = flag_n_val.width;
	else
		ret = print_len;
	return (ret);
}

int	d_with_zero_padding(t_list flag_n_val, int *ptr, int print_len)
{
	int ret;

	ret = 0;
	if (flag_n_val.zero_padding == 0)
		return (0);
	if (*ptr < 0)
	{
		ret = 1; // 마이너스 부호 개수 추가.
		ft_putchar('-'); //zero padding이 있으면 음수가 제일 먼저 나와야 한다.
		ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
		*ptr = ft_abs(*ptr);
	}
	else
		ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	return (ret);
}

int	d_conversion(t_list flag_n_val, va_list *ap)
{
	int ret;
	int ptr;
	int print_len;

	ret = 0;
	ptr = va_arg(*ap, int);
	print_len = ft_len(ptr);
	if (flag_n_val.precision == 1)
		flag_n_val.zero_padding = 0;
	ret = d_with_zero_padding(flag_n_val, &ptr, print_len);
	if (flag_n_val.precision == 1)
		ret = d_with_precision(flag_n_val, ptr, print_len);
	else
		ret += d_without_precision(flag_n_val, ptr, print_len);
	return (ret);
}

int	u_with_precision(t_list flag_n_val, unsigned int ptr, int print_len)
{
	char	*tmp;
	int		ret;
	
	flag_n_val.zero_padding = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	if (print_len > flag_n_val.precision_len)
		ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	else
		ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_zero(flag_n_val.precision_len, print_len, 0, 1);
	tmp = ft_itoa(ptr);
	write(1, tmp, print_len);
	free(tmp);
	if (print_len > flag_n_val.precision_len)
		ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	else
		ft_pad_right_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len || flag_n_val.precision_len > print_len)
		ret = ft_max(flag_n_val.width, flag_n_val.precision_len);
	else
		ret = print_len;
	return (ret);
}

int	u_without_precision(t_list flag_n_val, unsigned int ptr, int print_len)
{
	char	*tmp;
	int		ret;
	
	ret = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	tmp = ft_itoa(ptr);
	write(1, tmp, print_len);
	free(tmp);
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len)
		ret = flag_n_val.width;
	else
		ret = print_len;
	return (ret);
}

int	u_conversion(t_list flag_n_val, va_list *ap)
{
	unsigned int    ptr;
	int             print_len;
	int				ret;

	ret = 0;
	ptr = va_arg(*ap, int);
	print_len = ft_len(ptr);
	if (flag_n_val.precision == 1)
		ret = u_with_precision(flag_n_val, ptr, print_len);
	else
		ret = u_without_precision(flag_n_val, ptr, print_len);
	return (ret);
}

int	low_x_with_precision(t_list flag_n_val, unsigned int ptr, int print_len)
{
	int ret;

	ret = 0;
	flag_n_val.zero_padding = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	if (print_len > flag_n_val.precision_len)
		ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	else
		ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_zero(flag_n_val.precision_len, print_len, 0, 1);
	ft_putnbr_base(ptr, "0123456789abcdef");
	if (print_len > flag_n_val.precision_len)
		ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	else
		ft_pad_right_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len || flag_n_val.precision_len > print_len)
		ret = ft_max(flag_n_val.width, flag_n_val.precision_len);
	else
		ret = print_len;
	return (ret);
}

int	low_x_without_precision(t_list flag_n_val, unsigned int ptr, int print_len)
{
	int ret;

	ret = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_putnbr_base(ptr, "0123456789abcdef");
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len)
		ret = flag_n_val.width;
	else
		ret = print_len;
	return (ret);
}

int	low_x_conversion(t_list flag_n_val, va_list *ap)
{
	int				ret;
	unsigned int	ptr;
	int             print_len;
	
	ret = 0;
	ptr = va_arg(*ap, int);
	print_len = ft_converted_len(ptr, "0123456789abcdef");
	if (flag_n_val.precision == 1)
		ret = low_x_with_precision(flag_n_val, ptr, print_len);
	else
		ret = low_x_without_precision(flag_n_val, ptr, print_len);
	return (ret);
}

int	cap_x_with_precision(t_list flag_n_val, unsigned int ptr, int print_len)
	
{
	int ret;
	
	ret = 0;
	flag_n_val.zero_padding = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	if (print_len > flag_n_val.precision_len)
		ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	else
		ft_pad_left_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_zero(flag_n_val.precision_len, print_len, 0, 1);
	ft_putnbr_base(ptr, "0123456789ABCDEF");
	if (print_len > flag_n_val.precision_len)
		ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	else
		ft_pad_right_blank(flag_n_val.width, flag_n_val.precision_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len || flag_n_val.precision_len > print_len)
		ret = ft_max(flag_n_val.width, flag_n_val.precision_len);
	else
		ret = print_len;
	return (ret);
}

int	cap_x_without_precision(t_list flag_n_val, unsigned int ptr, int print_len)
{
	int ret;
	
	ret = 0;
	ft_pad_left_zero(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_pad_left_blank(flag_n_val.width, print_len, flag_n_val.left_align, flag_n_val.zero_padding);
	ft_putnbr_base(ptr, "0123456789ABCDEF");
	ft_pad_right_blank(flag_n_val.width, print_len, flag_n_val.left_align);
	if (flag_n_val.width > print_len)
		ret = flag_n_val.width;
	else
		ret = print_len;
	return (ret);
}

int	cap_x_conversion(t_list flag_n_val, va_list *ap)
{
	int				ret;
	unsigned int	ptr;
	int             print_len;

	ret = 0;
	ptr = va_arg(*ap, int);
	print_len = ft_converted_len(ptr, "0123456789ABCDEF");
	if (flag_n_val.precision == 1)
		ret = cap_x_with_precision(flag_n_val, ptr, print_len);
	else
		ret = cap_x_without_precision(flag_n_val, ptr, print_len);
	return (ret);
}

int ft_print_till_percent(const char **format)
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

void ft_left_n_zeroflag(const char **format, t_list *flag_n_val)
{
	if (**format == '-')
		{
			(*flag_n_val).left_align = 1;
			++(*format);
		}
		if (**format == '0')
		{
			(*flag_n_val).zero_padding = 1;
			++(*format);
		}
		if (**format == '-' && **(format - 2) != '-')
		{
			(*flag_n_val).left_align = 1;
			++(*format);
		}
}

void	ft_read_width(const char **format, t_list *flag_n_val, va_list *ap)
{
	if ((**format >= '1' && **format <= '9') || **format == '*')
	{
		if (**format == '*')
		{
			(*flag_n_val).width = va_arg(*ap, int);
			if ((*flag_n_val).width < 0)
			{
				(*flag_n_val).width = ft_abs((*flag_n_val).width);
				(*flag_n_val).left_align = 1;
			}
			++(*format);
		}
		else
		{
			(*flag_n_val).width = ft_atoi(*format);
			while(ft_is_numeric(**format))
				++(*format);
		}
	}
}
void	ft_read_precision(const char **format, t_list *flag_n_val, va_list *ap)
{
	if (**format == '.')
	{
		(*flag_n_val).precision = 1;
		++(*format);
	}
	if ((**format >= '0' && **format <= '9') || **format == '*')
	{
		if (**format == '*')
		{
			(*flag_n_val).precision_len = va_arg(*ap, int);
			++(*format);
		}
		else
		{
			(*flag_n_val).precision_len = ft_atoi(*format);
			while (ft_is_numeric(**format))
				++(*format);
		}
	}
}

int	ft_process_formatting(const char **format, t_list flag_n_val, va_list *ap)
{
	int ret;
	
	ret = 0;
	ret += ft_print_till_percent(format);
	ft_left_n_zeroflag(format, &flag_n_val);
	ft_read_width(format, &flag_n_val, ap);
	ft_read_precision(format, &flag_n_val, ap);
	if (**format == 'c')
		ret += c_conversion(flag_n_val, ap);
	else if (**format == 's')
		ret += s_conversion(flag_n_val, ap);
	else if (**format == 'p')
		ret += p_conversion(flag_n_val, ap);
	else if (**format == 'd' || **format == 'i')
		ret += d_conversion(flag_n_val, ap);
	else if (**format == 'u')
		ret += u_conversion(flag_n_val, ap);
	else if (**format == 'x')
		ret += low_x_conversion(flag_n_val, ap);
	else if (**format == 'X')
		ret += cap_x_conversion(flag_n_val, ap);
	else if (**format == '%')
		ft_putchar('%');
	++(*format);
	return (ret);	
}

int     ft_printf(const char *format, ...)
{
    va_list ap;
	t_list	flag_n_val;
	int		ret;

    ret = 0;
	va_start(ap, format);
    while (*format != '\0')
    {
        if (ft_strchr(format, '%'))
		{
        	flag_n_val.width = 0;
			flag_n_val.left_align = 0;
			flag_n_val.zero_padding = 0;
			flag_n_val.precision = 0;
			flag_n_val.precision_len = 0;
			ret += ft_process_formatting(&format, flag_n_val, &ap);
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


int main(void)
{/*
    char str1[100] = "I'm going to bed in %05c minutes %05c second. Good night!\n";
    char c = 'c';
    char d = 'd';

    char str2[50] = "Here comes %020s !!\n";
    char s[20] = "Queen B";

    char str3[100] = "The address of a is %010p and that of b is %-10p\n";
    int a = 200;

    char str4[100] = "The value of (a, b) is (%07d, %07d)\n";
    long long b = 25789;
	
    char str5[100] = "The value of (a, b) is (%-7u, %020u)\n";
    long long e = -257;
	
	char str6[100] = "The value of (a, b) is (%010x, %10x)\n";
	
	char str7[100] = "The value of (a, b) is (%-10X, %-010X)\n";
	
	char str8[30] = "To print %%%% !!\n";
	
	char str9[100] = "%10s\n";
    char f[10] = "big";

    ft_printf(str1, c, d);
    printf(str1, c, d);

    ft_printf(str2, s);
    printf(str2, s);

    ft_printf(str3, a, b);
    printf(str3, a, b);
    
    ft_printf(str4, a, b);
    printf(str4, a, b);
	
    ft_printf(str5, a, e);
    printf(str5, a, e);
	
	ft_printf(str6, a, e);
    printf(str6, a, e);
	
	ft_printf(str7, a, e);
    printf(str7, a, e);

	ft_printf(str8, a);
    printf(str8, a);
	
	ft_printf(str9, f);
    printf(str9, f);

    printf("len : %d\n", ft_converted_len(200, "0123456789abcdef"));
    ft_putnbr_base(200, "0123456789abcdef");
    ft_printf("\n");
*/

    char str10[100] = "I'm going to bed in %010.10c minutes %010.09c second. Good night! %s\n";
    char g = 'g';
    char h = 'h';
	printf("%d\n", ft_printf(str10, g, h, "guys"));
    printf("%d\n", printf(str10, g, h, "guys"));

	printf("%d\n", ft_printf("%c", '\0'));
    printf("%d\n", printf("%c", '\0'));
	
    char str11[50] = "Here comes %010.2s and %s!\n";
    char s11[20] = "Queen A";
    char s12[20] = "Queen B";
    ft_printf(str11, s11, s12);
    printf(str11, s11, s12);
	printf("%d\n", ft_printf(str11, s11, s12));
	printf("%d\n", printf(str11, s11, s12));
	

    char str12[100] = "The address of p is %020p and that of q is %-10p\n";
    int p = 200;
    long long q = 25789;
	printf("%d\n", ft_printf(str12, &p, &q));
	printf("%d\n", printf(str12, &p, &q));

    char str13[100] = "The value of (a, b) is (%2.10d, %10.10d)\n";
    int a = 200;
    long long b = -123;

    ft_printf(str13, a, b);
    printf(str13, a, b);
	printf("%d\n", ft_printf(str13, a, b));
	printf("%d\n", printf(str13, a, b));

    char str14[100] = "The value of (h, i) is (%-08.15u, %.020u)\n";
    int i = 200;
    long long j = 257;

	printf("%d\n", ft_printf(str14, i, j));
	printf("%d\n", printf(str14, i, j));


    char str15[100] = "The value of (i, j) is (%10.2x, %10x)\n";

	printf("%d\n", ft_printf(str15, i, j));
	printf("%d\n", printf(str15, i, j));

    char str16[100] = "The value of (a, b) is (%*.*X, %-010X)\n";

	printf("%d\n", ft_printf(str16, 10, 7, i, j));
	printf("%d\n", printf(str16, 10, 7, i, j));


    /*
    char str8[30] = "To print %%% ";
    
    ft_printf(str8, a);
    printf("\n");
    printf(str8, a);
    printf("\n");

    char str9[30] = "% z!! % \n";
    ft_printf(str9, 15);
    printf(str9, 15);

    
    ft_printf("%.000000006d\n", a);
    printf("%.000000006d\n", a);
    */

    return (0);
}
