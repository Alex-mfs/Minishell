/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:49:52 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:49:55 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Converts a lowercase character into uppercase (if possible)
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
