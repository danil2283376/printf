/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:55:45 by scolen            #+#    #+#             */
/*   Updated: 2020/12/10 19:06:56 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	output_accuracy_string(int end, char *s, global_varible *g_varible, int boolean)
{
	int start;
	int length_string;

	start = 0;
	length_string = ft_strlen(s);
	if (boolean)
	{
		while (start < end)
			write(1, &s[start++], 1);
		g_varible->length = g_varible->length + start;
	}
	else
	{
		if (g_varible->accuracy <= length_string && g_varible->exist_accuracy)
			length_string = g_varible->accuracy;
	}
	return (length_string);
}

static void	continue_string(char *s/*, va_list *va_args*/, global_varible *g_varible)
{
	int length_string;
	// int new_len_nbr;
	int start;
	int new_width;
	// int varible_value;

	// length_number = len_number(number);
	length_string = ft_strlen(s);
	start = 0;
	length_string = output_accuracy_string(length_string, s, g_varible, 0);
	new_width = new_width1(g_varible->width, length_string/*, number*/);
	if (g_varible->width >= 0)
		output_width_int/*string*/(0, new_width, g_varible, 's');
	output_accuracy_string(length_string, s, g_varible, 1);
	if (g_varible->width < 0)
		output_width_int/*string*/(0, new_width, g_varible, 's');
}

static int	threatment_null(global_varible *g_varible, char **str)
{
	int value_is_null;

	value_is_null = 0;
	if (*str == NULL && g_varible->accuracy < 0)
	{
		*str = ft_strdup("(null)");
		value_is_null = 1;
		g_varible->accuracy = 6;
	}
	else if (*str == NULL)
	{
		*str = ft_strdup("(null)");
		value_is_null = 1;
	}
	return (value_is_null);
}

void	threatment_string(const char *s, va_list *va_args, global_varible *g_varible)
{
	char *str;
	int value_is_null;

	value_is_null = 0;
	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	// printf("accuracy: %d", g_varible->accuracy);
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 's');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	str = va_arg(*va_args, char *); // строка из аргумента
	value_is_null = threatment_null(g_varible, &str);
	continue_string(str/*, va_args*/, g_varible);
	if (value_is_null)
		free(str);
	zeroing_value(g_varible);
	va_end(*va_args);
}
