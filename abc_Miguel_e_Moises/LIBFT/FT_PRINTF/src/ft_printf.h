/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:35:55 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:58 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../src/libft.h"

int		ft_strout(const char *format, t_list **lst, va_list ap);
int		ft_parsemarker(const char *format, unsigned int *i, \
		t_list **lst, va_list ap);
int		ft_type(const char *format, unsigned int *i, t_list **lst, va_list ap);
int		ft_type_c(t_list **lst, va_list ap);
int		ft_type_s(t_list **lst, va_list ap);
int		ft_type_p(t_list **lst, va_list ap);
int		ft_type_di(t_list **lst, va_list ap);
int		ft_type_u(t_list **lst, va_list ap);
int		ft_type_x(t_list **lst, va_list ap, char type);
int		ft_type_perc(t_list **lst);
void	ft_lstprint(t_list *lst, int fd, void (*ft_printtype)(char *, int));
int		*ft_intdup(int n);
char	*ft_dec2hexptr(size_t n, char type);
char	*ft_itoa_u(unsigned int n);
char	*ft_dec2hex(size_t n, char type);

#endif
