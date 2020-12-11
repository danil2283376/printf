/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_procent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:42:49 by scolen            #+#    #+#             */
/*   Updated: 2020/12/11 14:48:54 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		zero_exist_procent(const char *str)
{
	int start;

	start = 0;
	while (str[start - 1] != '%')
		start--;
	if (str[start] == '0')
		return (1);
	return (0);
}

static void	substitution_value_width_proc(const char *s, global_varible *g_varible, va_list *va_args, char symbol)
{
	int start;
	int number_negative;

	start = 0;
	number_negative = 0;
	while (s[start - 1] != '%')
		start--;
	while (s[start] != '-' && s[start] != '*'
		&& s[start] != symbol && s[start] != '.')
		start++;
	if (s[start] == '-')
	{
		number_negative = 1;
		start++;
	}
	while (s[start] != '*' && s[start] != symbol && s[start] != '.')
		start++;
	if (s[start] == '*')
	{
		g_varible->width = va_arg(*va_args, int);
		if (number_negative == 1 && g_varible->width > 0)
			g_varible->width = g_varible->width * (-1);
	}
	va_end(*va_args);
}

static void	output_width_procent(int length_number, int number_width, global_varible *g_varible, char symbol)
{
	int start;
	char symbol1;
	int boolean_zero;
	int symbol_negative;
	int boolean;

	start = 0;
	(void)symbol;
	symbol1 = ' ';
	symbol_negative = 0;
	boolean = 0;
	boolean_zero = zero_exist_procent(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, symbol);
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	if (boolean_zero == 1 && (g_varible->exist_accuracy == -1 ||
		g_varible->exist_accuracy == 0) && symbol_negative == 0)
			symbol1 = '0';
	while (length_number++ < number_width)
		ft_putchar_fd(symbol1, 1, g_varible);
		// write(1, &symbol1, 1);
}

static void	continue_procent(/*const char *s, va_list *va_args, */global_varible *g_varible)
{
	int len_str;

	if (g_varible->width < 0)
		len_str = g_varible->width + 1;
	else
		len_str = g_varible->width - 1;
	// printf("g_varible->width: %d", len_str);
	if (g_varible->width >= 0)
		output_width_procent(0, len_str, g_varible, '%');
	// printf("%d", len_str);
	ft_putchar_fd('%', 1, g_varible);
	// write(1, "%", 1);
	if (g_varible->width < 0)
	{
		// printf("HGHJFKL");
		// printf("len_str: %d\n", len_str);
		if (len_str < 0)
	 		len_str = len_str * (-1);
		output_width_procent(0, len_str, g_varible, '%');
	}
}

void	threatment_procent(const char *s, va_list *va_args, global_varible *g_varible)
{
	int start;

	start = 0;
	// printf("char = %c\n", s[start]);
	g_varible->width = take_width_procent(&s[start - 1]);
	g_varible->str = &s[0];
	substitution_value_width_proc(&s[0], g_varible, va_args, '%');
	continue_procent(/*s, va_args, */g_varible);
	zeroing_value(g_varible);
}
