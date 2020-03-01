/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_to_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:38:48 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		complete_the_pipe(char **str)
{
	char	**tab;
	int		j;

	j = 3;
	if (ft_strchr(str[0], '|') == NULL)
		return (1);
	tab = pipe_line(str[0]);
	while (j != 1)
	{
		if (tab[1] != NULL)
			j = error_pipe(tab, str[0]);
		else
			j = 2;
		if (j == 0)
			return (0);
		if (j == 2)
		{
			help_to_finish_the_pipe(&str[0]);
			free_2d(tab);
			tab = pipe_line(str[0]);
		}
	}
	free_2d(tab);
	return (1);
}

void	help_to_finish_the_pipe(char **line)
{
	char	*new;
	char	*str;
	int		i;

	i = 0;
	new = NULL;
	while (!i || search_no_espace(new) == 0)
	{
		i++;
		ft_memdel(&new);
		new = ft_readline("> ");
	}
	if (!new && i)
	{
		save_historique(line[0], 1);
		ft_memdel(&line[0]);
	}
	str = line[0];
	line[0] = ft_strjoin(line[0], new);
	free(new);
	free(str);
}

int		check_redirections(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_one_by_one(str[i]) == 0 || check_if_h_file(str[i]) == 0)
		{
			ft_putendl("42sh: syntax error near unexpected token `newline'");
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_one_by_one(char *line)
{
	int i;
	int b;
	int a;

	a = 0;
	b = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != '<' && line[i] != '>')
		{
			a = 0;
			b = 0;
		}
		if (line[i] == '>')
			a++;
		if (line[i] == '<')
			b++;
		if ((a > 0 && b > 0) || a > 2 || b > 2)
			return (0);
		i++;
	}
	return (1);
}

int		check_if_h_file(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			while (line[i] && (line[i] == '>' || line[i] == '<'))
				i++;
			if (search_no_espace(&line[i]) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
