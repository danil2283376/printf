/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:35:41 by scolen            #+#    #+#             */
/*   Updated: 2020/12/13 11:50:48 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef	struct	s_varible
{
	int			index_main_str;
	const char	*str;
	int			length;
	int			accuracy;
	int			exist_accuracy;
	int			width;
	int			zero_exist;
	int			start;
	int			number;
	int			flag;
}				t_varible;

char			*ft_strdup(const char *str);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_toupper(int ch);
void			ft_putchar_fd(char c, int fd,
		t_varible *g_varible);
char			*ft_itoa_u(unsigned int n);
int				ft_printf(const char *s, ...);
int				take_width(const char *s);
int				take_accuracy(const char *s, t_varible *g_varible);
int				zero_exist(const char *str);
int				negative_exist(const char *str, char symbol);
int				len_number(long nbr);
void			output_width_int(int length_number,
		int number_width, t_varible *g_varible, char symbol);
void			output_accuracy_int(int length_number,
		int number_accuracy, long number, t_varible *g_varible);
int				new_width1(int width, int length_number);
void			substitution_value_width(const char *s,
		t_varible *g_varible, va_list *va_args, char symbol);
void			substitution_value_accuracy(const char *s,
		t_varible *g_varible, va_list *va_args);
void			zeroing_value(t_varible *g_varible);
void			threatment_unsigned(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_integer(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_int(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_string(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_char(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_hex(const char *s,
		va_list *va_args, t_varible *g_varible);
int				count_devisions(long number);
char			value_hex(int symbol);
void			threatment_hex_h(const char *s,
		va_list *va_args, t_varible *g_varible);
void			threatment_p(const char *s,
		va_list *va_args, t_varible *g_varible);
int				take_width_procent(const char *s);
int				negative_exist_procent(const char *str, char symbol);
void			threatment_procent(const char *s,
		va_list *va_args, t_varible *g_varible);
#endif
