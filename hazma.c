/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hazma.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:08:04 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**pipe_line(char *line)
{
	char	**pipe;

	pipe = ft_strsplit(line, '|');
	return (pipe);
}

int		len(char const *s, char c)
{
	int start;
	int end;
	int i;

	i = 0;
	end = 0;
	start = 0;
	while (s[start] != '\0')
	{
		while (s[start] == c && s[start] != '\0')
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while (s[end] != c && s[end] != '\0')
			end++;
		start = end;
		i++;
	}
	return (i);
}

int		error_pipe(char **str, char *line)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (search_no_espace(str[i]) == 0 && (str[i + 1] != NULL
					|| (str[i + 1] == NULL && leno_pipe(line, '|') > i)))
		{
			ft_putstr("42sh: parse error near `|'\n");
			return (0);
		}
		else if (str[i + 1] == NULL && (search_no_espace(str[i]) == 0
					|| leno_pipe(line, '|') > i))
			return (2);
		i++;
	}
	return (1);
}

int		search_no_espace(char *str)
{
	int i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int		leno_pipe(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j++;
			while (str[i] == c)
				i++;
			i--;
		}
		i++;
	}
	return (j);
}
