/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_with_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:41:40 by hiantrin          #+#    #+#             */
/*   Updated: 2020/01/17 12:51:07 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*replace_with_env(char *line, t_env_list *env, int b)
{
	int		i;
	char	*str;
	int		a;

	i = 0;
	b = 0;
	while (line[i])
	{
		if (line[i] == '$' && (i == 0 || (line[i - 1] != 92 &&
			line[i - 1] != 39)))
		{
			a = i + 1;
			str = help_replace_env(&a, line, i, env);
			if (str != NULL)
				b = ft_strlen(str);
			if (str != NULL)
				join_with_something(&line, str, a, i);
			else
				join_with_anything2(&line, str, a, i);
			i = i + b;
		}
		else
			i++;
	}
	return (line);
}

char	*help_replace_env(int *a, char *line, int i, t_env_list *env)
{
	char	*new;
	char	*str;

	while (line[*a] == '_' || (line[*a] >= 'a' && line[*a] <= 'z') ||
			(line[*a] >= 'A' && line[*a] <= 'Z') ||
			(line[*a] >= '0' && line[*a] <= '9'))
		(*a)++;
	new = ft_strsub(line, i + 1, *a - (i + 1));
	if (new[0] == '\0')
		str = ft_strsub(line, i, *a - i);
	else
		str = check_env(new, env);
	free(new);
	return (str);
}

void	join_with_something(char **line, char *str, int a, int i)
{
	char	*first;
	char	*new;

	first = ft_strsub(*line, 0, i);
	new = ft_strjoin(first, str);
	free(first);
	free(str);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(new, str);
	free(new);
	free(str);
}

void	join_with_anything2(char **line, char *str, int a, int i)
{
	char	*first;

	first = ft_strsub(*line, 0, i);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(first, str);
	free(first);
	free(str);
}

char	*check_env(char *str, t_env_list *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (ft_strdup(env->environ));
		else
			env = env->next;
	}
	return (NULL);
}
