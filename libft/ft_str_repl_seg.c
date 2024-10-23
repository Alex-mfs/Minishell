// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_str_repl_seg.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
// /*   Updated: 2024/10/19 18:12:22 by joao-rib         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// char	*ft_str_repl_seg(char *str, char *old, char *new)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	len;
// 	size_t	l2;
// 	char	*str2;

// 	i = 0;
// 	j = 0;
// 	if (!str || !old)
// 		return (NULL);
// 	len = ft_strlen(str);
// 	l2 = ft_strlen(old);
// 	if (l2 > len)
// 		return (str);
// 	l2 = len - l2 + ft_strlen(new);
// 	str2 = ft_calloc(l2, sizeof(char *));
// 	if (!str2)
// 		return (str);
// 	while (i <= len)
// 	{
// 		if (str[i] == old[0])
// 		{
// 			str[i] = new;
// 			times--;
// 			if (times <= 0)
// 				break ;
// 		}
// 		else
// 			str2[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	free(str);
// 	return (str2);
// }
