#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h> // va_start, va_arg, va_copy, va_end

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

void    ft_putstr(const char *s)
{
    int i;

    i = 0;
    while(s[i] != '\0')
    {
        write(1, &s[i], 1);
        ++i;
    }
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

void    ft_putnbr_two(int n)
{
    long nb;

    nb = n;
    if (nb < 0)
    {
        ft_putchar('-');
        nb *= -1;
    }
    if (nb >= 0)
    {
        ft_putnbr_two(nb / 10);
        ft_putnbr_two(nb % 10);
    }
    else
        ft_putchar(nb + '0');
}

int     ft_printf(const char *format, ...)
{
    va_list ap;
    
    va_start(ap, format);
    while(*format != '\0')
    {
        if (ft_strchr(format, '%'))
        {
            while(format != ft_strchr(format, '%'))
            {
                write(1, format, 1);
                ++format;
            }
            ++format;
            if (*format == 'c')
                ft_putchar(va_arg(ap, int));
            else if (*format == 's')
			{
                char	*ptr;
				ptr = va_arg(ap, char*);
				write(1, ptr, ft_strlen(ptr));
			}
            else if (*format == 'p')
            {
				char	*ptr;
				ptr = va_arg(ap, char*);
				write(1, "0x", 2);
				ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
            }
            else if (*format == 'd' || *format == 'i')
            {
				int ptr;
				ptr = va_arg(ap, int);
				write(1, ft_itoa(ptr), ft_len(ptr));
            }
			else if (*format == 'u')
			{
				unsigned int ptr;
				ptr = va_arg(ap, int);
				//write(1, ft_itoa(ptr), ft_len(ptr));
                ft_putnbr_two(ptr);
			}
			else if (*format == 'x')
			{
				unsigned int	ptr;
				ptr = va_arg(ap, int);
				ft_putnbr_base(ptr, "0123456789abcdef");
            }
			else if (*format == 'X')
			{
				unsigned int	ptr;
				ptr = va_arg(ap, int);
				ft_putnbr_base(ptr, "0123456789ABCDEF");
            }
			else if (*format == '%')
				ft_putchar('%');
			else
			{
				ft_putchar('%');
				write(1, format, 1);
			}
			++format;			
        }
        else
        {
            ft_putstr(format);
            break ;
        }
    }
    va_end(ap);
    return (0); 
}




int main(void)
{
    char str1[100] = "I'm going to bed in %c minutes %c second. Good night!\n";
    char c = 'c';
    char d = 'd';

    char str2[30] = "Here comes %s\n";
    char s[20] = "Queen B";

    char str3[100] = "The address of a is %p and that of b is %p\n";
    int a = 200;

    char str4[100] = "The value of (a, b) is (%d, %d)\n";
    long long b = 25789;
	
    char str5[100] = "The value of (a, b) is (%u, %u)\n";
    long long e = -257;
	
	char str6[100] = "The value of (a, b) is (%x, %x)\n";
	
	char str7[100] = "The value of (a, b) is (%X, %X)\n";
	
	char str8[30] = "To print %%%%%%% !!\n";
	
	char str9[100] = "The value of (a, b) is (%-d, %-d)\n";
	
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

	ft_printf(str8, '%');
    printf(str8, '%');
	
	printf(str9, a, e);

    return (0);
}