/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:49:25 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:49:28 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Converts an uppercase character into lowercase (if possible)
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
