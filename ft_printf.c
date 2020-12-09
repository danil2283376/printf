/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:22:52 by scolen            #+#    #+#             */
/*   Updated: 2020/12/09 19:49:27 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int		manage_fuction1(const char *s, global_varible *g_varible, va_list *va_args)
{
	if (s[g_varible->start] == 'x')
	{
		threatment_hex(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'X')
	{
		threatment_hex_h(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'p')
	{
		threatment_p(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start + 1] == '%')
	{
		g_varible->start++;
		threatment_procent(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	return (0);
}

int		manage_fuction2(const char *s, global_varible *g_varible, va_list *va_args)
{
	if (s[g_varible->start] == 'i')
	{
		threatment_integer(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 's')
	{
		threatment_string(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	else if (s[g_varible->start] == 'c')
	{
		threatment_char(&s[g_varible->start], va_args, g_varible);
		return (1);
	}
	return (0);
}

void	manage_fuction(const char *s, global_varible *g_varible, va_list *va_args)
{
	g_varible->start = 0;
	while (s[g_varible->start])
	{
		if (s[g_varible->start] == 'd')
		{
			threatment_int(&s[g_varible->start], va_args, g_varible);
			break ;
		}
		else if (s[g_varible->start] == 'u')
		{
			threatment_unsigned(&s[g_varible->start], va_args, g_varible);
			break ;
		}
		else if (manage_fuction2(s, g_varible, va_args))
			break ;
		else if (manage_fuction1(s, g_varible, va_args))
			break ;
		g_varible->start++;
	}
	(*g_varible).index_main_str = (*g_varible).index_main_str + g_varible->start;
	g_varible->start = 0;
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
			g_varible->accuracy = 0;
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
	// char *ptr = "Hello World";
	// ft_printf("%0*.5s\n", 15, ptr);
	// printf("%0*.5s", 15, ptr);
	// ft_printf("%.00s", "\0");
	// static char *s_hidden = "hi low\0don't print me lol\0";
	// ft_printf("%0000s", s_hidden);
	// printf("%0000s", s_hidden);
	#pragma endregion

	#pragma region char
	// ft_printf("%010.5c\n", '1' + '5');
	// printf("%010.5c", '1' + '5');
	// ft_printf("%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c",(char)128,(char)129,(char)130,(char)131,(char)132,(char)133,(char)134,(char)135,(char)136,(char)137,(char)138,(char)139,(char)140,(char)141,(char)142,(char)143,(char)144,(char)145,(char)146,(char)147,(char)148,(char)149,(char)150,(char)151,(char)152,(char)153,(char)154,(char)155,(char)156,(char)157,(char)158,(char)159,(char)160,(char)161,(char)162,(char)163,(char)164,(char)165,(char)166,(char)167,(char)168,(char)169,(char)170,(char)171,(char)172,(char)173,(char)174,(char)175,(char)176,(char)177,(char)178,(char)179,(char)180,(char)181,(char)182,(char)183,(char)184,(char)185,(char)186,(char)187,(char)188,(char)189,(char)190,(char)191,(char)192,(char)193,(char)194,(char)195,(char)196,(char)197,(char)198,(char)199,(char)200,(char)201,(char)202,(char)203,(char)204,(char)205,(char)206,(char)207,(char)208,(char)209,(char)210,(char)211,(char)212,(char)213,(char)214,(char)215,(char)216,(char)217,(char)218,(char)219,(char)220,(char)221,(char)222,(char)223,(char)224,(char)225,(char)226,(char)227,(char)228,(char)229,(char)230,(char)231,(char)232,(char)233,(char)234,(char)235,(char)236,(char)237,(char)238,(char)239,(char)240,(char)241,(char)242,(char)243,(char)244,(char)245,(char)246,(char)247,(char)248,(char)249,(char)250,(char)251,(char)252,(char)253,(char)254,(char)255);
	// printf("\n%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c%-1c%-2c%-3c%-4c",(char)128,(char)129,(char)130,(char)131,(char)132,(char)133,(char)134,(char)135,(char)136,(char)137,(char)138,(char)139,(char)140,(char)141,(char)142,(char)143,(char)144,(char)145,(char)146,(char)147,(char)148,(char)149,(char)150,(char)151,(char)152,(char)153,(char)154,(char)155,(char)156,(char)157,(char)158,(char)159,(char)160,(char)161,(char)162,(char)163,(char)164,(char)165,(char)166,(char)167,(char)168,(char)169,(char)170,(char)171,(char)172,(char)173,(char)174,(char)175,(char)176,(char)177,(char)178,(char)179,(char)180,(char)181,(char)182,(char)183,(char)184,(char)185,(char)186,(char)187,(char)188,(char)189,(char)190,(char)191,(char)192,(char)193,(char)194,(char)195,(char)196,(char)197,(char)198,(char)199,(char)200,(char)201,(char)202,(char)203,(char)204,(char)205,(char)206,(char)207,(char)208,(char)209,(char)210,(char)211,(char)212,(char)213,(char)214,(char)215,(char)216,(char)217,(char)218,(char)219,(char)220,(char)221,(char)222,(char)223,(char)224,(char)225,(char)226,(char)227,(char)228,(char)229,(char)230,(char)231,(char)232,(char)233,(char)234,(char)235,(char)236,(char)237,(char)238,(char)239,(char)240,(char)241,(char)242,(char)243,(char)244,(char)245,(char)246,(char)247,(char)248,(char)249,(char)250,(char)251,(char)252,(char)253,(char)254,(char)255);
	#pragma endregion

	// ft_printf("%.5.5d", 15);
	#pragma region hex(x)
	// ft_printf("%8.3x\n", 8375);
	// printf("%8.3x", 8375);
	// ft_printf("%-10.5x", 12345678);
	// printf("%-10.5x", 12345678);
	// ft_printf("%-5.0x", 0);
	// printf("%-5.0x", 0);
	#pragma endregion

	#pragma region pointer
	// char *p;
	// printf("%*.5d\n", 15, -5);
	// ft_printf("%*.5d\n", 15, -5);
	#pragma endregion

	#pragma region procent
	// printf("%010%\n", 10);
	// printf("%0*% %10% %-10% %10.5d\n", 10, 228);
	// ft_printf("%0*% %10% %-10% %10.5d\n", 10, 228);
	// ft_printf("%10%\n");
	// printf("%10%\n");
	#pragma endregion

	#pragma region all_flag
	// ft_printf("%d, %010.5X\n", 10, 1337);
	// printf("%d, %010.5X\n", 10, 1337);
	// ft_printf("%10.5d, %*.*u %i, %-10.5x, %010.5X, %p, %s %10c\n", 228, 15, 5, 1000, 1337, 12345678, 43, NULL, NULL, '?');
	// printf("%10.5d, %*.*u %i, %-10.5x, %010.5X, %p, %s %10c\n", 228, 15, 5, 1000, 1337, 12345678, 43, NULL, NULL, '?');
	// while (1);
	ft_printf("%10.5d, %*.*u %i, %010.5X, %p, %s %10c\n", 228, 15, 5, 1337, 12345678, 43, NULL, NULL, '?');
	printf("%10.5d, %*.*u %i, %010.5X, %p, %s %10c\n", 228, 15, 5, 1337, 12345678, 43, NULL, NULL, '?');

	// ft_printf("%15......10d", 99999);
	// printf("%15......10d", 99999);
	#pragma endregion

	// printf("danil %10.4% whats up\n");
	// ft_printf("danil %10.4% whats up");
}
