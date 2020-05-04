
#include "ft_print.h"

int     ft_printf(const char *format, ...)
{
	va_list ap;
	int		ret;
	int		each_ret;

	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (ft_strchr(format, '%'))
		{
			each_ret = ft_process_formatting(&format, &ap);
			if (each_ret == -1)
				return (-1);
			else
				ret += each_ret;
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
{
	/*
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
	char str10[100] = "I'm going to bed in %10c minutes %010.09c second. Good night! %s\n";
	char g = 'g';
	char h = 'h';
	printf("%d\n", ft_printf(str10, g, h, "guys"));
	printf("%d\n", printf(str10, g, h, "guys"));

	printf("%d\n", ft_printf("%c", '\0'));
	printf("%d\n", printf("%c", '\0'));
	
	char str11[50] = "Here comes %10.2s and %s!\n";
	char s11[20] = "Queen A";
	char s12[20] = "Queen B";
	printf("%d\n", ft_printf(str11, s11, s12));
	printf("%d\n", printf(str11, s11, s12));
	

	char str12[100] = "The address of p is %20p and that of q is %-10p\n";
	int p = 200;
	long long q = 25789;
	printf("%d\n", ft_printf(str12, &p, &q));
	printf("%d\n", printf(str12, &p, &q));

	char str13[100] = "The value of (a, b) is (%020.15d, %10.10d)\n";
	int a = -2147483647;
	long long b = 123;

	printf("%d\n", ft_printf(str13, a, b));
	printf("%d\n", printf(str13, a, b));

	char str14[100] = "The value of (h, i) is (%-08.15u, %.10u)\n";
	int i = 200;
	long long j = -257;

	printf("%d\n", ft_printf(str14, i, j));
	printf("%d\n", printf(str14, i, j));


	char str15[100] = "The value of (i, j) is (%10.2x, %10x)\n";

	printf("%d\n", ft_printf(str15, i, j));
	printf("%d\n", printf(str15, i, j));

	char str16[100] = "The value of (a, b) is (%*.*X, %-010X)\n";

	printf("%d\n", ft_printf(str16, 10, 7, i, j));
	printf("%d\n", printf(str16, 10, 7, i, j));


	
	char str8[30] = "To print %%% ";
	
	ft_printf(str8, a);
	printf("\n");
	printf(str8, a);
	printf("\n");

	char str9[30] = "% z!! % \n";
	ft_printf(str9, 15);
	printf(str9, 15);

	
	ft_printf("%d\n", a);
	printf("%d\n", a);
	

	return (0);
}
