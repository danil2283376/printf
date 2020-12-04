/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:22:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/04 22:47:06 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct	struct_global_varible
{
	int			index_main_str;
	const char	*str;
	int			length;
	int			accuracy;
	int			exist_accuracy;
	int			width;
}				global_varible;

int	len_number(long nbr)
{
	int len_nbr;
	int start;

	len_nbr = 0;
	start = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = nbr * (-1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len_nbr++;
	}
	return (len_nbr);
}

// передать указатель строки с начала флага(s, c, d, и так далее)
int		take_width(const char *s/*, global_varible *g_varibleva_list *va_args*/)
{
	int start;
	int number;
	int value_zero;

	start = 0;
	number = 0;
	value_zero = 0;
	while (s[start] != '%' && s[start])
		start--;
	while (s[start + 1] == '0')
	{
		value_zero = 1;
		start++;
	}
	number = ft_atoi(&s[start + 1]);
	// if (value_zero = 1 && va_args->accuracy == 0)
	// printf("\nnumber: %d\n", number);
	return (number);
}

// передать указатель строки с начала флага(s, c, d, и так далее)
int		take_accuracy(const char *s, global_varible *g_varible/*, va_list *va_args, */)
{
	int start;
	int number_accuracy;

	start = 0;
	number_accuracy = 0;
	while (s[start] != '.' && s[start] != '%' && s[start])
		start--;
	if (s[start] != '.')
	{
		g_varible->exist_accuracy = 0;
		return (0);
	}
	number_accuracy = ft_atoi(&s[start + 1]);
	if (number_accuracy < 0)
		return (0);
	//printf("%d", number_accuracy);
	return (number_accuracy);
}
// передать значение начинающееся с флага (d,c,s итд)
int		zero_exist(const char *str)
{
	int start;

	start = 0;
	while (str[start] != '%')
		start--;
	if (str[start + 1] == '0')
		return (1);
	return (0);
}

int		negative_exist(const char *str, char symbol)
{
	int start;
	int symbol_negative;

	start = 0;
	symbol_negative = 0;
	while (str[start] != '%')
		start--;
	while (str[start] != '-' && str[start] != '.' && str[start] != symbol)
		start++;
	if (str[start] == '-')
		return (1);
	return (0);
}

#pragma region threatment_d
// принимает длину числа в символах, и число ширины
void	output_width_int(int length_number, int number_width, global_varible *g_varible)
{
	int start;
	char symbol;
	int boolean_zero;
	int symbol_negative;

	start = 0;
	symbol = ' ';
	symbol_negative = 0;
	boolean_zero = zero_exist(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, 'd');
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	if (boolean_zero == 1 && g_varible->exist_accuracy == 0
		&& symbol_negative == 0)
		symbol = '0';
	while (length_number++ < number_width)
		write(1, &symbol, 1);
}

// длина числа в символах, и число точности, и само число
void	output_accuracy_int(int length_number, int number_accuracy, long number, int accuracy)
{
	if (accuracy == 0)
		number_accuracy = 0;
	if (number_accuracy < 0)
		number_accuracy = 0;
	if (number < 0)
	{
		write(1, "-", 1);
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
	}
	while (length_number++ < number_accuracy)
		write(1, "0", 1);
}

int		new_width1(int width, int length_number/*, int number*/)
{
	if (width < 0)
	{
		width = width * (-1);
		// if (number < 0)
		// 	length_number = length_number + 1;
		// printf("length_number: %d", length_number);
		width = width - length_number;
	}
	else
	{
		// if (number < 0)
		// 	length_number = length_number + 1;
		width = width - length_number;
	}
	// printf("width: %d", width);
	return (width);
}

void	continue_thretment_int(global_varible *g_varible, int number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	start_number = 0;
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_int(0, new_width, g_varible);
	output_accuracy_int(length_number, new_len_nbr, number, g_varible->accuracy);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible);
}
// строка начинается с флага
void	substitution_value_width(const char *s, global_varible *g_varible, va_list *va_args, char symbol)
{
	int start;
	int number_negative;

	start = 0;
	number_negative = 0;
	while (s[start] != '%')
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
// строка начинается с флага
void	substitution_value_accuracy(const char *s, global_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start] != '.' && s[start] != '%')
		start--;
	if (s[start] != '.')
		return ;
	else
	{
		if (s[start + 1] == '*')
		{
			g_varible->accuracy = va_arg(*va_args, int);
			// printf("accuracy: %d\n", g_varible->accuracy);
		}
	}
	va_end(*va_args);
}

void	threatment_int(const char *s, va_list *va_args, global_varible *g_varible)
{
	int number_from_args;
	// int accuracy;
	// int width;
	char *number_str;

	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 'd');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, int); // число из аргумента
	// printf("number_from_args: %d\n", number_from_args);
	if (number_from_args == 0 && g_varible->accuracy == 0)
	{
		number_str = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
		number_str = ft_itoa(number_from_args); // число в строке
	continue_thretment_int(g_varible, number_from_args, number_str); // продолжение
	free(number_str);
	va_end(*va_args);
}
#pragma endregion

#pragma region threatment_unsigned
void	output_width_unsigned(int length_number, int number_width, global_varible *g_varible)
{
	int start;
	char symbol;
	int boolean_zero;
	int symbol_negative;

	start = 0;
	symbol = ' ';
	symbol_negative = 0;
	boolean_zero = zero_exist(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, 'u');
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	if (boolean_zero == 1 && g_varible->exist_accuracy == 0
		&& symbol_negative == 0)
		symbol = '0';
	while (length_number++ < number_width)
		write(1, &symbol, 1);
}

// длина числа в символах, и число точности, и само число
void	output_accuracy_unsigned(int length_number, int number_accuracy, long number, int accuracy)
{
	if (accuracy == 0)
		number_accuracy = 0;
	if (number_accuracy < 0)
		number_accuracy = 0;
	if (number < 0)
	{
		write(1, "-", 1);
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
	}
	while (length_number++ < number_accuracy)
		write(1, "0", 1);
}

int		new_width_unsigned(int width, int length_number/*, int number*/)
{
	if (width < 0)
	{
		width = width * (-1);
		// if (number < 0)
		// 	length_number = length_number + 1;
		// printf("length_number: %d", length_number);
		width = width - length_number;
	}
	else
	{
		// if (number < 0)
		// 	length_number = length_number + 1;
		width = width - length_number;
	}
	// printf("width: %d", width);
	return (width);
}

void	continue_thretment_unsigned(global_varible *g_varible, long number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	start_number = 0;
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width_unsigned(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_unsigned(0, new_width, g_varible);
	output_accuracy_unsigned(length_number, new_len_nbr, number, g_varible->accuracy);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (g_varible->width < 0)
		output_width_unsigned(0, new_width, g_varible);
}
// строка начинается с флага
void	substitution_value_width_u(const char *s, global_varible *g_varible, va_list *va_args, char symbol)
{
	int start;
	int number_negative;

	start = 0;
	number_negative = 0;
	while (s[start] != '%')
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
// строка начинается с флага
void	substitution_value_accuracy_u(const char *s, global_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start] != '.' && s[start] != '%')
		start--;
	if (s[start] != '.')
		return ;
	else
	{
		if (s[start + 1] == '*')
		{
			g_varible->accuracy = va_arg(*va_args, int);
			// printf("accuracy: %d\n", g_varible->accuracy);
		}
	}
	va_end(*va_args);
}

void	threatment_unsigned(const char *s, va_list *va_args, global_varible *g_varible)
{
	long number_from_args;
	// int accuracy;
	// int width;
	char *number_str;

	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width_u(&s[0], g_varible, va_args, 'u');
	substitution_value_accuracy_u(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, unsigned int); // число из аргумента
	// printf("number_from_args: %u\n", number_from_args);
	if (number_from_args == 0 && g_varible->accuracy == 0)
	{
		number_str = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
		number_str = ft_itoa_u(number_from_args); // число в строке
	// printf("number_str: %s\n", number_str);
	continue_thretment_unsigned(g_varible, number_from_args, number_str); // продолжение
	free(number_str);
	va_end(*va_args);
}
#pragma endregion

#pragma region threatment_integer
void	output_width_integer(int length_number, int number_width, global_varible *g_varible)
{
	int start;
	char symbol;
	int boolean_zero;
	int symbol_negative;

	start = 0;
	symbol = ' ';
	symbol_negative = 0;
	boolean_zero = zero_exist(g_varible->str);
	symbol_negative = negative_exist(g_varible->str, 'i');
	if (length_number > number_width)
		return ;
	if (number_width < 0)
		number_width = number_width * (-1);
	if (length_number > number_width)
		return ;
	if (boolean_zero == 1 && g_varible->exist_accuracy == 0
		&& symbol_negative == 0)
		symbol = '0';
	while (length_number++ < number_width)
		write(1, &symbol, 1);
}

// длина числа в символах, и число точности, и само число
void	output_accuracy_integer(int length_number, int number_accuracy, long number, int accuracy)
{
	if (accuracy == 0)
		number_accuracy = 0;
	if (number_accuracy < 0)
		number_accuracy = 0;
	if (number < 0)
	{
		write(1, "-", 1);
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
	}
	while (length_number++ < number_accuracy)
		write(1, "0", 1);
}

int		new_width_i(int width, int length_number/*, int number*/)
{
	if (width < 0)
	{
		width = width * (-1);
		// if (number < 0)
		// 	length_number = length_number + 1;
		// printf("length_number: %d", length_number);
		width = width - length_number;
	}
	else
	{
		// if (number < 0)
		// 	length_number = length_number + 1;
		width = width - length_number;
	}
	// printf("width: %d", width);
	return (width);
}

void	continue_thretment_integer(global_varible *g_varible, int number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = g_varible->accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	start_number = 0;
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width_i(g_varible->width, new_len_nbr/*, number*/);
	if (g_varible->width >= 0)
		output_width_integer(0, new_width, g_varible);
	output_accuracy_integer(length_number, new_len_nbr, number, g_varible->accuracy);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (g_varible->width < 0)
		output_width_integer(0, new_width, g_varible);
}
// строка начинается с флага
void	substitution_value_width_i(const char *s, global_varible *g_varible, va_list *va_args, char symbol)
{
	int start;
	int number_negative;

	start = 0;
	number_negative = 0;
	while (s[start] != '%')
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
// строка начинается с флага
void	substitution_value_accuracy_i(const char *s, global_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start] != '.' && s[start] != '%')
		start--;
	if (s[start] != '.')
		return ;
	else
	{
		if (s[start + 1] == '*')
		{
			g_varible->accuracy = va_arg(*va_args, int);
			// printf("accuracy: %d\n", g_varible->accuracy);
		}
	}
	va_end(*va_args);
}

void	threatment_integer(const char *s, va_list *va_args, global_varible *g_varible)
{
	int number_from_args;
	// int accuracy;
	// int width;
	char *number_str;

	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width_i(&s[0], g_varible, va_args, 'i');
	substitution_value_accuracy_i(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, int); // число из аргумента
	// printf("number_from_args: %d\n", number_from_args);
	if (number_from_args == 0 && g_varible->accuracy == 0)
	{
		number_str = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width + 1;
		else
			g_varible->width = g_varible->width - 1;
	}
	else
		number_str = ft_itoa(number_from_args); // число в строке
	continue_thretment_integer(g_varible, number_from_args, number_str); // продолжение
	free(number_str);
	va_end(*va_args);
}
#pragma endregion

#pragma region string

int	output_accuracy_string(int end, char *s, global_varible *g_varible, int boolean)
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
		// while (start < g_varible->accuracy)
		// 	start++;
		// printf("%d", g_varible->accuracy);
		if (g_varible->accuracy <= length_string)
			length_string = g_varible->accuracy;
	}
	return (length_string);
}

void	continue_string(char *s, va_list *va_args, global_varible *g_varible)
{
	int length_string;
	int new_len_nbr;
	int start;
	int new_width;
	int varible_value;

	// length_number = len_number(number);
	length_string = ft_strlen(s);
	start = 0;
	length_string = output_accuracy_string(length_string, s, g_varible, 0);
	// printf("%d", g_varible->accuracy);
	// printf("%d", length_string);
	// new_len_nbr = g_varible->accuracy - length_number;
	// printf("%s", s);
	// if (length_string >= g_varible->accuracy)
	// {
	// 	varible_value = length_string - g_varible->accuracy;
	// 	if (varible_value < 0)
	// 		varible_value = 0;
	// 	if (g_varible->accuracy != 0)
	// 		length_string = length_string - varible_value;
	// }
	// printf("length_string: %d", length_string);
	new_width = new_width1(g_varible->width, length_string/*, number*/);
	if (g_varible->width >= 0)
		output_width_int(0, new_width, g_varible);
	// while (start < g_varible->accuracy)
	// 	write();
	output_accuracy_string(length_string, s, g_varible, 1);
	// while (start < ) // вывод строки по символам
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible);
}

void	threatment_string(const char *s, va_list *va_args, global_varible *g_varible)
{
	//смысл один и тот же просто выводить строку
	//и при точности обрезать строку
	char *number_from_args;
	int value_is_null;

	value_is_null = 0;
	g_varible->width = take_width(&s[0]); // ширина
	g_varible->accuracy = take_accuracy(&s[0], g_varible); // точность
	// printf("accuracy: %d", g_varible->accuracy);
	g_varible->str = &s[0]; // передал место с флагом (d)
	substitution_value_width(&s[0], g_varible, va_args, 's');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number_from_args = va_arg(*va_args, char *); // строка из аргумента
	if (number_from_args == NULL)
	{
		number_from_args = ft_strdup("(null)");
		value_is_null = 1;
		// printf("1%s", number_from_args);
	}
	// printf("%s", number_from_args);
	continue_string(number_from_args, va_args, g_varible);
	if (value_is_null)
		free(number_from_args);
	va_end(*va_args);
}
#pragma endregion

void	manage_fuction(const char *s, global_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start])
	{
		if (s[start] == 'd')
		{
			threatment_int(&s[start], va_args, g_varible);
			break ;
		}
		else if (s[start] == 'u')
		{
			threatment_unsigned(&s[start], va_args, g_varible);
			break ;
		}
		else if (s[start] == 'i')
		{
			threatment_integer(&s[start], va_args, g_varible);
			break ;
		}
		else if (s[start] == 's')
		{
			threatment_string(&s[start], va_args, g_varible);
			break ;
		}
		else if (s[start] == 'c')
		{

			break ;
		}
		else if (s[start] == 'x')
		{

			break ;
		}
		else if (s[start] == 'X')
		{

			break ;
		}
		else if (s[start] == 'p')
		{

			break;
		}
		start++;
	}
	g_varible->index_main_str = g_varible->index_main_str + start;   // elsi slomaetsya delay po derevenski
}

int		free_struct(global_varible *g_varible, va_list *va_args)
{
	free(g_varible);
	va_end(*va_args);
	return (-1);
}

int		ft_printf(const char *s, ...)
{
	int start;
	global_varible *g_varible;
	va_list va_args;

	start = 0;
	va_start(va_args, s);
	g_varible = malloc(sizeof(global_varible) * 1);
	if (g_varible == NULL)
		return (free_struct(g_varible, &va_args));
	g_varible->length = 0;
	while (s[start])
	{
		if (s[start] == '%')
		{
			g_varible->index_main_str = start; // присваиваю глобальному индексу, где остановился
			manage_fuction(&s[start], g_varible, &va_args); // обработчик флагов
			start = g_varible->index_main_str; // передвигаю индекс вперед
		}
		else
			write(1, &s[start], 1);
		start++;
		g_varible->length++;
	}
	free_struct(g_varible, &va_args);
	return (0);
}

int main()
{
	#pragma region integer
	// ft_printf("%-5d*\n", 52625);
	// printf("%-5d*\n", 52625);

	// ft_printf("this %d* number\n", 17);
	// printf("this %d* number\n", 17);

	// ft_printf("%d\n",  2147483647);
	// printf("%d\n",  2147483647);

	// ft_printf("%d\n", (int)(-2147483678));
	// printf("%d\n", (int)(-2147483678));

	// ft_printf("%0-8.5d\n", 34);
	// printf("%0-8.5d", 34);

	// ft_printf("%0-8.5d\n", 0);
	// printf("%0-8.5d", 0);

	// ft_printf("5414151%0-3.3d\n", -8462);
	// printf("%0-3.3d", -8462);

	// ft_printf("%0-10.2d\n", -8462);
	// printf("%0-10.2d", -8462);

	#pragma region С нулями работает как часы
	// ft_printf("%-5.d\n", 0);
	// printf("%-5.d", 0);
	#pragma endregion
	#pragma endregion

	#pragma region unsigned int
	// ft_printf("%.5u\n", 2);
	// printf("%.5u", 2);
	#pragma endregion

	#pragma region *.*
	// ft_printf("%d,DANIL %u,HELLO %i\n", 10, 5, 4294967295U, (int)2147483647);
	// printf("%d,DANIL %u,HELLO %i", 10, 5, 4294967295U, (int)2147483647);
	#pragma endregion

	#pragma region i
	// ft_printf("%u, %d, this %i number\n", (int)(2147483678), (int)(-2147483678), 17);
	// printf("%u, %d, this %i number", (int)(2147483678), (int)(-2147483678), 17);
	#pragma endregion

	#pragma region string
	// printf("%012.10d", 12345678);
	// printf("%5.2s\n", "Hello");
	ft_printf("%010.6s\n", NULL);
	printf("%010.6s", NULL);
	#pragma endregion
}
