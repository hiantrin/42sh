/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:12:15 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		help_redirect(char *file)
{
	int		p[2];
	char	*line;

	pipe(p);
	while (1)
	{
		line = NULL;
		while (line == NULL || search_no_espace(line) == 0)
		{
			ft_memdel(&line);
			line = ft_readline("herdoc> ");
			if (!line)
			{
				ft_memdel(&line);
				line = ft_strdup(file);
			}
		}
		if (ft_strcmp(line, file) == 0)
			break ;
		ft_putendl_fd(line, p[1]);
		ft_memdel(&line);
	}
	ft_memdel(&line);
	close(p[1]);
	return (p[0]);
}

int		redirect_with_fd(char *line, int *i)
{
	int		j;
	char	*str;
	int		b;

	j = i[0];
	j--;
	while (j != -1 && line[j] && line[j] != ' ' &&
		line[j] != '\t' && line[j] != '\n')
		j--;
	j++;
	if (i[0] == j)
		return (-1);
	else
		str = ft_strsub(line, j, i[0] - j);
	b = -1;
	while (str[++b])
		if (str[b] < 48 || str[b] > 57)
		{
			free(str);
			return (-1);
		}
	i[0] = j;
	j = atoi(str);
	free(str);
	return (j);
}

int		print_p_d(char *file, int *pipe)
{
	ft_putstr_fd("42sh: ", pipe[1]);
	ft_putstr_fd(file, pipe[1]);
	ft_putendl_fd(": Permission denied", pipe[1]);
	return (0);
}

int		print_n_x(char *file, int *pipe)
{
	ft_putstr_fd("42sh: ", pipe[1]);
	ft_putstr_fd(file, pipe[1]);
	ft_putendl_fd(": no such file or directory", pipe[1]);
	return (0);
}

int		print_i_d(char *file, int *pipe)
{
	ft_putstr_fd("42sh: ", pipe[1]);
	ft_putstr_fd(file, pipe[1]);
	ft_putendl_fd(": Is a directory", pipe[1]);
	return (0);
}
