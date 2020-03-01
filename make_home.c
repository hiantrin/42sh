/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:52:12 by hiantrin          #+#    #+#             */
/*   Updated: 2020/01/17 12:48:20 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*replace_home(char *line, t_env_list *env)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (line[i] == '~' && (i == 0 || line[i - 1] == ' ' ||
			line[i - 1] == '\t'))
			i = help_replace_home2(&line, i, env);
		else
			i++;
	}
	return (line);
}

int		help_replace_home2(char **line, int i, t_env_list *env)
{
	char	*str;
	int		a;

	if (line[0][i + 1] == '/' || line[0][i + 1] == ' ' ||
		line[0][i + 1] == '\0' || line[0][i + 1] == '\t')
	{
		str = check_env("HOME", env);
		a = i + 1;
		if (str != NULL)
			join_with_something(&line[0], str, a, i);
		else
			join_with_anything2(&line[0], str, a, i);
		i = a;
	}
	else
		i = help_replace_home(&line[0], i);
	return (i);
}

int		help_replace_home(char **line, int i)
{
	char	**command;
	int		a;
	char	*str;
	char	*new;

	a = i;
	while (line[0][a] && line[0][a] != ' ' && line[0][a] != '\t')
		a++;
	str = ft_strsub(line[0], i + 1, a - (i + 1));
	command = (char **)malloc(sizeof(char *) * 2);
	command[1] = NULL;
	command[0] = ft_strdup("/Users");
	new = str;
	str = check_if_exist(str, command);
	free(new);
	free_2d(command);
	if (str != NULL)
		join_with_something(&line[0], str, a, i);
	i = a;
	return (i);
}

char	*check_if_exist(char *command, char **env)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if (str != NULL)
			free_2d(str);
		str = ls(env[i]);
		j = 0;
		while (str[j])
		{
			if (ft_strcmp(str[j], command) == 0)
				break ;
			j++;
		}
		if (str[j] != NULL)
			break ;
		i++;
	}
	return (help_to_concate(env[i], str, j));
}

char	*help_to_concate(char *first, char **str, int j)
{
	char	*new;

	if (first != NULL)
	{
		new = concate(first, str[j]);
		free_2d(str);
	}
	else
	{
		if (str != NULL)
			free_2d(str);
		new = NULL;
	}
	return (new);
}
