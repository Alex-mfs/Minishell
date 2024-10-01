/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:52:25 by joao-rib          #+#    #+#             */
/*   Updated: 2024/09/25 19:14:53 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>

int main(void)
{
	char	*prompt;
	char	*suffix;

    prompt = "\033[1m""\033[32m""Curr.Directory:""\033[0m""\033[32m";
    suffix = "\033[0m""\n""|""\033[4m""\033[97m""Input your command:""\033[0m";
    printf("%s~%s%s\n", prompt, getcwd(NULL, 4096), suffix);
    return (1);
}

