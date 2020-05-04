#ifndef FT_PRINT_H
# define FT_PRINT_H

#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_list
{
	int width;
	int left;
	int zero;
	int precision;
	int precs_len;
	
}				t_list;

int			ft_strlen(const char *s);
void		ft_putchar(const char c);
int			ft_putstr(const char *s);
void		ft_putnbr(long long n);
char		*ft_strchr(const char *s, int c);

void		ft_putnbr_base(unsigned long long nb, const char *base);
int			ft_converted_len(unsigned long long nb, const char *base);
long long	ft_abs(long long n);
long long	ft_len(long long n);
char		*ft_itoa(int n);

int			ft_is_space(const char c);
int			ft_is_numeric(const char c);
int			ft_atoi(const char *str);

void		ft_pad_right_blnk(int width, int print_len, int left);
void		ft_pad_left_blnk(int width, int print_len, int left, int zero);
void		ft_pad_left_zero(int width, int print_len , int left, int zero);
int			ft_max(int width, int precs_len);

int			c_conversion(t_list opt, va_list *ap);
int			s_conversion(t_list opt, va_list *ap);
int			percent_conversion(t_list opt);

int			p_with_precision(t_list opt, char *ptr, int print_len);
int			p_without_precision(t_list opt, char *ptr, int print_len);
int			p_conversion(t_list opt, va_list *ap);

int			d_negative_print(t_list opt, int *ptr, int *print_len);
int			d_positive_print(t_list opt, int ptr, int print_len);
void		ft_d_conversion_pad_right_blnk(t_list opt, int print_len);
int			d_with_precision(t_list opt, int ptr, int print_len);
int			d_without_precision(t_list opt, int ptr, int print_len);

int			d_with_zero_padding(t_list opt, int *ptr, int print_len);
int			d_conversion(t_list opt, va_list *ap);

int			u_with_precision(t_list opt, unsigned int ptr, int print_len);
int			u_without_precision(t_list opt, unsigned int ptr, int print_len);
int			u_conversion(t_list opt, va_list *ap);

int			low_x_with_precision(t_list opt, unsigned int ptr, int print_len);
int			low_x_without_precision(t_list opt, unsigned int ptr, int print_len);
int			low_x_conversion(t_list opt, va_list *ap);

int			cap_x_with_precision(t_list opt, unsigned int ptr, int print_len);
int			cap_x_without_precision(t_list opt, unsigned int ptr, int print_len);
int			cap_x_conversion(t_list opt, va_list *ap);

int			ft_print_till_percent(const char **format);
void		ft_left_n_zeroflag(const char **format, t_list *opt);
void		ft_read_width(const char **format, t_list *opt, va_list *ap);
void		ft_read_precision(const char **format, t_list *opt, va_list *ap);

int			ft_type_conversion(const char **format, t_list opt, va_list *ap);
int			ft_process_formatting(const char **format, va_list *ap);

#endif