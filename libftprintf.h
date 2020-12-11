/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:35:41 by scolen            #+#    #+#             */
/*   Updated: 2020/12/11 18:44:25 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct	struct_global_varible
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
}				global_varible;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_tolower(int ch);
int					ft_toupper(int ch);
int					ft_isprint(int ch);
int					ft_isascii(int ch);
int					ft_isalnum(int ch);
int					ft_isdigit(int arg);
int					ft_isalpha(int c);
int					ft_atoi(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_strnstr(const char *big,
		const char *little, size_t len);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strchr(const char *str, int ch);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
void				*ft_memchr(const void *arr, int c, size_t n);
void				*ft_memmove(void *destination,
		const void *source, size_t n);
void				*ft_memccpy(void *destination,
		const void *source, int c, size_t n);
void				*ft_memcpy(void *destination, const void *source, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *destination, int c, size_t n);
void				*ft_calloc(size_t num, size_t size);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst,
		void *(*f)(void *), void (*del)(void *));

void				ft_putchar_fd(char c, int fd,
		global_varible *g_varible);
char				*ft_itoa_u(unsigned int n);
int					ft_printf(const char *s, ...);
int					take_width(const char *s);
int					take_accuracy(const char *s, global_varible *g_varible);
int					zero_exist(const char *str);
int					negative_exist(const char *str, char symbol);
int					len_number(long nbr);
void				output_width_int(int length_number,
		int number_width, global_varible *g_varible, char symbol);
void				output_accuracy_int(int length_number,
		int number_accuracy, long number, global_varible *g_varible);
int					new_width1(int width, int length_number);
void				substitution_value_width(const char *s,
		global_varible *g_varible, va_list *va_args, char symbol);
void				substitution_value_accuracy(const char *s,
		global_varible *g_varible, va_list *va_args);
void				zeroing_value(global_varible *g_varible);
void				threatment_unsigned(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_integer(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_int(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_string(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_char(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_hex(const char *s,
		va_list *va_args, global_varible *g_varible);
int					count_devisions(long number);
char				value_hex(int symbol);
void				threatment_hex_h(const char *s,
		va_list *va_args, global_varible *g_varible);
void				threatment_p(const char *s,
		va_list *va_args, global_varible *g_varible);
int					take_width_procent(const char *s);
int					negative_exist_procent(const char *str, char symbol);
void				threatment_procent(const char *s,
		va_list *va_args, global_varible *g_varible);
#endif
