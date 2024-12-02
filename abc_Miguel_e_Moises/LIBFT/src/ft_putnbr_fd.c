/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:46:05 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:46:08 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Outputs the integer n to the given file descriptor
#include "libft.h"

static void	putnbr_fd_recursive(unsigned int nb, int fd)
{
	if ((nb / 10) != 0)
		putnbr_fd_recursive((nb / 10), fd);
	ft_putchar_fd((nb % 10 + '0'), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n2;

	if (n < 0)
	{
		n2 = -n;
		ft_putchar_fd('-', fd);
	}
	else
		n2 = n;
	putnbr_fd_recursive(n2, fd);
}
