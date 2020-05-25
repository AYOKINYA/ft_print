/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkang <jkang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:40:50 by jkang             #+#    #+#             */
/*   Updated: 2020/05/19 18:15:03 by jkang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_list
{
	int			width;
	int			width_neg;
	int			left;
	int			zero;
	int			zero_original;
	int			precision;
	int			precs_len;
	int			precs_star;
}				t_list;

int				ft_strlen(const char *s);
void			ft_putchar(const char c);
int				ft_putstr(const char *s);
void			ft_putnbr(long long n);
char			*ft_strchr(const char *s, int c);

void			ft_putnbr_base(unsigned long long nb, const char *base);
int				ft_converted_len(unsigned long long nb, const char *base);
long long		ft_abs(long long n);
int				ft_len(long long n);
char			*ft_itoa(long long n);

int				ft_is_space(const char c);
int				ft_is_numeric(const char c);
int				ft_atoi(const char *str);

void			ft_pad_right_blnk(int width, int print_len, int left);
void			ft_pad_left_blnk(int width, int print_len, int left, int zero);
void			ft_pad_left_zero(int width, int print_len, int left, int zero);
int				ft_max(int width, int precs_len);
int				ft_strcmp(const char *s1, const char *s2);

int				c_conversion(t_list opt, va_list *ap);
int				s_conversion(t_list opt, va_list *ap);
int				percent_conversion(t_list opt);

char			*ft_strdup(const char *s);
void			p_with_precision_body(t_list opt, unsigned long ptr,
													int *print_len, char *str);
int				p_with_precision(t_list opt, unsigned long ptr,
									int *print_len, char *str);
int				p_without_precision(t_list opt, unsigned long ptr,
									int print_len, char *str);
int				p_conversion(t_list opt, va_list *ap);

int				d_negative_print(t_list opt, long *ptr, int *print_len);
int				d_positive_print(t_list opt, long ptr, int print_len);
void			ft_d_conversion_pad_right_blnk(t_list opt,
												long ptr, int print_len);
void			d_with_precision_pad_left_blnk(t_list opt, long ptr,
															int print_len);
int				d_with_precision(t_list opt, long ptr, int print_len);

int				d_with_zero_padding(t_list opt, long *ptr, int *print_len);
void			d_info_check(t_list *opt, long *ptr, int *print_len);
int				d_without_precision(t_list opt, long ptr, int print_len);
int				d_conversion(t_list opt, va_list *ap);

int				u_with_precision(t_list opt, unsigned int ptr, int print_len);
int				u_without_precision(t_list opt, unsigned int ptr,
															int print_len);
int				u_conversion(t_list opt, va_list *ap);

int				low_x_with_precision(t_list opt, unsigned int ptr,
															int print_len);
int				low_x_without_precision(t_list opt, unsigned int ptr,
															int print_len);
int				low_x_conversion(t_list opt, va_list *ap);

int				cap_x_with_precision(t_list opt, unsigned int ptr,
															int print_len);
int				cap_x_without_precision(t_list opt, unsigned int ptr,
															int print_len);
int				cap_x_conversion(t_list opt, va_list *ap);

int				ft_print_till_percent(const char **format);
void			ft_left_n_zeroflag(const char **format, t_list *opt);
void			ft_read_width(const char **format, t_list *opt, va_list *ap);
void			ft_read_precision(const char **format, t_list *opt,
																va_list *ap);

int				ft_type_conversion(const char **format, t_list opt,
																va_list *ap);
int				ft_process_formatting(const char **format, va_list *ap);

#endif
