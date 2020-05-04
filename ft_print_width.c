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

int     ft_printf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    while(*format != '\0')
    {
        if (ft_strchr(format, '%'))
        {
            int width = 0;
            int left_align = 0;
            int zero_padding = 0;
            int precision = 0;
            int precision_len = 0;
            while(format != ft_strchr(format, '%'))
            {
                write(1, format, 1);
                ++format;
            }
            ++format;
            if (*format == '-')
            {
                left_align = 1;
                ++format;
            }
            if (*format == '0')
            {
                zero_padding = 1;
                ++format;
            }
            if (*format == '-')
            {
                left_align = 1;
                ++format;
            }
			if (*format >= '1' && *format <= '9')
			{
				width = ft_atoi(format);
				while(ft_is_numeric(*format))
					++format;
			}
            if (*format == '.')
            {
                precision = 1;
                ++format;
            }
            if (*format >= '0' && *format <= '9')
			{
				precision_len = ft_atoi(format);
				while(ft_is_numeric(*format))
					++format;
			}
            if (*format == 'c')
            {
                ft_pad_left_blank_char(width, 1, left_align);
                ft_putchar(va_arg(ap, int));
                ft_pad_right_blank(width, 1, left_align);
            }
            else if (*format == 's')
			{
                char	*ptr;
                int     print_len;

				ptr = va_arg(ap, char*);
                print_len = ft_strlen(ptr);
                if (precision == 1)
                {
                    if (print_len >= precision_len)
                        print_len = precision_len;
                }
                ft_pad_left_blank_char(width, print_len, left_align);
				write(1, ptr, print_len);
                ft_pad_right_blank(width, print_len, left_align);
			}
            else if (*format == 'p')
            {
				char	*ptr;
                int     print_len;

				ptr = va_arg(ap, char*);
                print_len = ft_len((unsigned long long)ptr) - 1;
                if (precision_len != 0)
                {
                    if (precision_len <= print_len - 2) //0x 제외
                        ft_pad_left_blank(width, print_len, 0, 0);
                    else
                        ft_pad_left_blank(width, precision_len + 2, 0, 0);
                }
                else
                    ft_pad_left_blank(width, print_len, left_align, zero_padding);
                write(1, "0x", 2);
                if (precision == 1)
                {
                    if ((precision_len > print_len - 2))
                    {
                        ft_pad_left_zero(precision_len, print_len - 2, 0, 1);
                    }
                }
                else
                    ft_pad_left_zero(width, print_len, left_align, zero_padding);
				ft_putnbr_base((unsigned long long)ptr, "0123456789abcdef");
                if (precision_len <= 0)
                    ft_pad_right_blank(width, print_len, left_align);
            }
            else if (*format == 'd' || *format == 'i')
            {
				int ptr;
                int print_len;

				ptr = va_arg(ap, int);
                print_len = ft_len(ptr);
                if (precision == 1) //precision 있으면 zero flag는 무효화한다.
                    zero_padding = 0;
                if (zero_padding == 1)
                {
                    if (ptr < 0)
                    {
                        ft_putchar('-'); //zero padding이 있으면 음수가 제일 먼저 나와야 한다.
                        ft_pad_left_zero(width, print_len, left_align, zero_padding);
                        ptr = ft_abs(ptr);
                    }
                    else
                        ft_pad_left_zero(width, print_len, left_align, zero_padding);
                }
                if (precision == 1 && left_align != 1) //precision 있고 left_align이 아니면 오른쪽 정렬이라 left_black precision 고려해 실행한다.
                {   
                    if (print_len > precision_len)
                        ft_pad_left_blank(width, print_len, left_align, zero_padding);
                    else
                    {   if (ptr < 0)
                            ft_pad_left_blank(width, precision_len + 1, left_align, zero_padding);
                        else
                            ft_pad_left_blank(width, precision_len, left_align, zero_padding);
                    }
                }
                else
                    ft_pad_left_blank(width, print_len, left_align, zero_padding);
                if (precision == 1) //precision == 1이고 precision_len이 print_len보다 긴 경우 그 차이만큼 0으로 채워준다. (당연히 zero_padding은 0이다.)
                {
                    if (ptr < 0)
                    {
                        ft_putchar('-'); //zero padding이 있으면 음수가 제일 먼저 나와야 한다.
                        ptr = ft_abs(ptr); //write할 때 필수로 ptr이 양수여야 한다.!!
                        print_len = ft_len(ptr);
                        ft_pad_left_zero(precision_len, print_len, 0, 1); // 0과 1을 직접 넣어준 이유는 ft_pad_left_zero를 사용하고자 하기 떄문이다.
                        write(1, ft_itoa(ptr), print_len);
                        print_len = ft_len(ptr) + 1;
                    }
                    else
                    {
                        ft_pad_left_zero(precision_len, print_len, 0, 1);
                        write(1, ft_itoa(ptr), print_len);
                    }
                }
                else
                    write(1, ft_itoa(ptr), print_len);
                if (precision == 1) // left_align == 1일 때 pad_right_blank 처리.
                {
                    if (print_len > precision_len)
                        ft_pad_right_blank(width, print_len, left_align);
                    else    // precision_len이 print_len보다 긴 경우 그 차이만큼 0으로 채워줬기 때문에 그 만큼 blank를 덜 출력해야 한다.
                        ft_pad_right_blank(width, precision_len + 1, left_align);
                }
                else
                    ft_pad_right_blank(width, print_len, left_align);
            }
			else if (*format == 'u')
			{
				unsigned int    ptr;
                int             print_len;

				ptr = va_arg(ap, int);
                print_len = ft_len(ptr);
                ft_pad_left_zero(width, print_len, left_align, zero_padding);
                ft_pad_left_blank(width, print_len, left_align, zero_padding);
				write(1, ft_itoa(ptr), ft_len(ptr));
                ft_pad_right_blank(width, print_len, left_align);
			}
			else if (*format == 'x')
			{
				unsigned int	ptr;
                int             print_len;

                ptr = va_arg(ap, int);
                print_len = ft_converted_len(ptr, "0123456789abcdef");
                ft_pad_left_zero(width, print_len, left_align, zero_padding);
                ft_pad_left_blank(width, print_len, left_align, zero_padding);
			    ft_putnbr_base(ptr, "0123456789abcdef");
                ft_pad_right_blank(width, print_len, left_align);
            }
			else if (*format == 'X')
			{
				unsigned int	ptr;
                int             print_len;

				ptr = va_arg(ap, int);
                print_len = ft_converted_len(ptr, "0123456789ABCDEF");
                ft_pad_left_zero(width, print_len, left_align, zero_padding);
                ft_pad_left_blank(width, print_len, left_align, zero_padding);
                ft_putnbr_base(ptr, "0123456789ABCDEF");
                ft_pad_right_blank(width, print_len, left_align);
            }
			else if (*format == '%')
				ft_putchar('%');
            else
			{
                if (*(format - 2) == '%')
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
    char str10[100] = "I'm going to bed in %010.10c minutes %010.09c second. Good night!\n";
    char g = 'g';
    char h = 'h';
    ft_printf(str10, g, h);
    printf(str10, g, h);

    char str11[50] = "Here comes %10.7s and %10.s\n";
    char s11[20] = "Queen A";
    char s12[20] = "Queen B";
    ft_printf(str11, s11);
    printf(str11, s12);


    char str12[100] = "The address of p is %-020p and that of q is %-10.7p\n";
    int p = 200;
    long long q = 25789;
    ft_printf(str12, &p, &q);
    printf(str12, &p, &q);

    char str4[100] = "The value of (a, b) is (%30.19d, %07d)\n";
    int a = 200;
    long long b = 4265489875;

    ft_printf(str4, a, b);
    printf(str4, a, b);
    
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