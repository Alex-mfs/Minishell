/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_export_aux_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfreire <alfreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:32:47 by alfreire          #+#    #+#             */
/*   Updated: 2024/12/03 13:58:46 by alfreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <string.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_sorted_export(char **sorted_env)
{
	int		i;
	char	*equals_sign;

	i = 0;
	while (sorted_env[i])
	{
		equals_sign = ft_strchr(sorted_env[i], '=');
		if (equals_sign)
			printf("declare -x %s\n", sorted_env[i]);
		else
			printf("declare -x %s=\"\"\n", sorted_env[i]);
		i++;
	}
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i + 1])
	{
		j = 0;
		while (env[j + 1])
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	add_new_env(char ***target_env, const char *assignment)
{
	int		i;
	char	**new_env_list;
	int		j;

	i = 0;
	j = 0;
	while ((*target_env)[i])
		i++;
	new_env_list = malloc(sizeof(char *) * (i + 2));
	if (!new_env_list)
		return ;
	while (j < i)
	{
		new_env_list[j] = (*target_env)[j];
		j++;
	}
	new_env_list[i] = ft_strdup(assignment);
	new_env_list[i + 1] = NULL;
	free(*target_env);
	*target_env = new_env_list;
}

int	find_env_index(char **target_env, const char *assigment)
{
	int		i;
	size_t	len;
	char	*key;

	key = ft_substr(assigment, 0, ft_strlen_sep(assigment, "="));
	len = ft_strlen(key);
	i = 0;
	while (target_env[i])
	{
		if (ft_strncmp(target_env[i], key, len) == 0 && \
		target_env[i][len] == '=')
		{
			free(key);
			return (i);
		}
		i++;
	}
	free(key);
	return (-1);
}
