/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:47:49 by scolen            #+#    #+#             */
/*   Updated: 2020/12/01 18:29:32 by scolen           ###   ########.fr       */
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
int		take_width(const char *s)
{
	int start;
	int number;

	start = 0;
	number = 0;
	while (s[start] != '%' && s[start])
		start--;
	while (s[start + 1] == '0')
		start++;
	number = ft_atoi(&s[start + 1]);
	// printf("\nnumber: %d\n", number);
	return (number);
}

// передать указатель строки с начала флага(s, c, d, и так далее)
int		take_accuracy(const char *s)
{
	int start;
	int number_accuracy;

	start = 0;
	number_accuracy = 0;
	while (s[start] != '.' && s[start] != '%' && s[start])
		start--;
	if (s[start] != '.')
		return (0);
	number_accuracy = ft_atoi(&s[start + 1]);
	if (number_accuracy < 0)
		return (0);
	//printf("%d", number_accuracy);
	return (number_accuracy);
}

#pragma region Обработка флага d
// передать указатель строки с начала флага(s, c, d, и так далее)
// int		boolean_zero_in_width(const char *s)
// {
// 	return (0);
// }

// принимает длину числа в символах, и число ширины
void	output_width_int(/*const char *s, */int length_number, int number_width/*, int number*/)
{
	int start;
	// int quantity_space;

	start = 0;
	if (length_number > number_width)
		return ;
	// if (number < 0)
	// 	length_number = length_number + 1;
	// printf("length_number: %d\n", length_number);
	// printf("number_width: %d\n", number_width);
	if (number_width < 0)
		number_width = number_width * (-1);
	// НЕ РАБОТАЕТ С ОТРИЦАТЕЛЬНЫМИ ЧИСЛАМИ
	if (length_number > number_width)
		return ;
	// printf("number_width: %d", number_width);
	while (length_number++ < number_width/*quantity_space*/)
		write(1, " ", 1);
	// if (boolean_zero_in_width == 1)
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
		// if (length_number < number_accuracy)
		// 	number_accuracy = number_accuracy + 1;
		number = number * (-1);
		number_accuracy = number_accuracy - 1;
		// number_accuracy = number_accuracy + 1;
	}
	// if ()
	// printf("\nlength_number = %d\n", number_accuracy);
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

// передаю аргументы числа        точности, ширину числа, само число, число в строке
void	continue_thretment_int(int accuracy, int width, int number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	start_number = 0;
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(width, new_len_nbr/*, number*/);
	if (width >= 0)
		output_width_int(0, new_width/*, number*/);
	output_accuracy_int(length_number, new_len_nbr, number, accuracy);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (width < 0)
		output_width_int(0, new_width/*, number*/);
}

// передать указатель строки с начала флага(s, c, d, и так далее)
void	threatment_int(const char *s, va_list *va_args)
{
	int number_from_args;
	int accuracy;
	int width;
	char *number_str;
	//int length_number;

	accuracy = take_accuracy(&s[0]); // точность
	width = take_width(&s[0]); // ширина
	number_from_args = va_arg(*va_args, int); // число из аргумента
	if (number_from_args == 0 && accuracy == 0)
	{
		number_str = ft_strdup("");
		if (width >= 0)
			width = width + 1;
		else
			width = width - 1;
	}
	else
		number_str = ft_itoa(number_from_args); // число в строке
	continue_thretment_int(accuracy, width, number_from_args, number_str); // продолжение
	free(number_str);
}
#pragma endregion

#pragma region Обработка флага u

void	continue_thretment_unsigned(int accuracy, int width, long number, char *number_str)
{
	int length_number;
	int new_len_nbr;
	int start_number;
	int new_width;

	length_number = len_number(number);
	new_len_nbr = accuracy - length_number; // 5 - 2 = 3
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + length_number; // 3 + 2 = 5
	start_number = 0;
	if (number < 0) // если число отрицательное
	{
		new_len_nbr = new_len_nbr + 1;
		start_number = 1;
	}
	new_width = new_width1(width, new_len_nbr/*, number*/);
	if (width >= 0)
		output_width_int(0, new_width/*, number*/);
	output_accuracy_int(length_number, new_len_nbr, number, accuracy);
	while (number_str[start_number]) // вывод числа по символам
		write(1, &number_str[start_number++], 1);
	if (width < 0)
		output_width_int(0, new_width/*, number*/);
}

void	threatment_unsigned(const char *s, va_list *va_args)
{
	unsigned int number_from_args;
	int accuracy;
	int width;
	char *number_str;
	//int length_number;

	accuracy = take_accuracy(&s[0]);
	width = take_width(&s[0]);
	number_from_args = va_arg(*va_args, unsigned int);
	if (number_from_args && accuracy == 0)
	{
		number_str = ft_strdup("");
		if (width >= 0)
			width = width + 1;
		else
			width = width - 1;
	}
	else
		number_str = ft_itoa_u(number_from_args);
	continue_thretment_unsigned(accuracy, width, number_from_args, number_str);
	free(number_str);
}

#pragma endregion
// начинает старт в строке с %
void	manage_fuction(const char *s, global_varible *g_varible, va_list *va_args)
{
	int start;

	start = 0;
	while (s[start])
	{
		if (s[start] == 'd')
		{
			threatment_int(&s[start], va_args);
			break ;
		}
		else if (s[start] == 'u')
		{
			threatment_unsigned(&s[start], va_args);
			break ;
		}
		else if (s[start] == 'i')
		{

			break ;
		}
		else if (s[start] == 's')
		{

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
		start++;
	}
	(*g_varible).index_main_str = (*g_varible).index_main_str + start;
}

int		ft_printf(const char *s, ...)
{
	int start;
	global_varible *g_varible;
	va_list va_args;

	start = 0;
	va_start(va_args, s);
	g_varible = malloc(sizeof(global_varible) * 1);
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
	}
	va_end(va_args);
	free(g_varible);
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

	ft_printf("5414151%0-3.3d\n", -8462);
	printf("%0-3.3d", -8462);

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

	#pragma region i
	#pragma endregion
}
