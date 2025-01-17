/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threatment_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:35:22 by scolen            #+#    #+#             */
/*   Updated: 2020/12/12 12:56:14 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	output_p(char *ptr, int count_devision, t_varible *g_varible)
{
	while (count_devision > 0 && ptr[count_devision - 1])
		ft_putchar_fd(ptr[--count_devision], 1, g_varible);
}

static int	threatment_value(char **ptr,
	long long number, int count_devision)
{
	int start;

	start = 0;
	while (start < count_devision && number >= 0)
	{
		(*ptr)[start] = value_hex(number % 16);
		number = number / 16;
		start++;
	}
	return (number);
}

static void	continue_thretment_p(char *ptr,
	int count_devision, long long number, t_varible *g_varible)
{
	int new_len_nbr;
	int new_width;

	new_len_nbr = g_varible->accuracy - count_devision;
	if (new_len_nbr < 0)
		new_len_nbr = 0;
	new_len_nbr = new_len_nbr + count_devision;
	number = threatment_value(&ptr, number, count_devision);
	new_width = new_width1(g_varible->width, new_len_nbr) - 2;
	if ((g_varible->width >= 0
		&& zero_exist(g_varible->str) == 0) || g_varible->exist_accuracy != 0)
		output_width_int(0, new_width, g_varible, 'p');
	ft_putchar_fd('0', 1, g_varible);
	ft_putchar_fd('x', 1, g_varible);
	if (g_varible->width >= 0
		&& zero_exist(g_varible->str) == 1 && g_varible->exist_accuracy == 0)
		output_width_int(0, new_width, g_varible, 'p');
	output_accuracy_int(count_devision, new_len_nbr, number, g_varible);
	output_p(ptr, count_devision, g_varible);
	if (g_varible->width < 0)
		output_width_int(0, new_width, g_varible, 'p');
}

static int	threatment_null(char **ptr,
	t_varible *g_varible, long long number)
{
	int count_devision;

	count_devision = 1;
	if (number == 0 && g_varible->exist_accuracy != 0
		&& g_varible->accuracy == 0)
	{
		*ptr = ft_strdup("");
		if (g_varible->width >= 0)
			g_varible->width = g_varible->width;
		else
			g_varible->width = g_varible->width;
		count_devision = 0;
	}
	else
	{
		count_devision = count_devisions(number);
		*ptr = malloc(count_devision * sizeof(char));
	}
	return (count_devision);
}

void		threatment_p(const char *s,
	va_list *va_args, t_varible *g_varible)
{
	long long	number;
	char		*ptr;
	int			count_devision;

	g_varible->width = take_width(&s[0]);
	g_varible->accuracy = take_accuracy(&s[0], g_varible);
	g_varible->str = &s[0];
	count_devision = 1;
	substitution_value_width(&s[0], g_varible, va_args, 'p');
	substitution_value_accuracy(&s[0], g_varible, va_args);
	number = (unsigned long)va_arg(*va_args, void *);
	count_devision = threatment_null(&ptr, g_varible, number);
	continue_thretment_p(ptr, count_devision, number, g_varible);
	zeroing_value(g_varible);
	free(ptr);
}
