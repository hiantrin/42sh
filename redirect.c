/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:11:56 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 18:53:07 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redirect(t_pi *pi, char **line, int *status, t_list *list)
{
	int		i;
	char	c;
	t_fornorme norme;

	norme.list = list;
	i = 0;
	while (line[0][i])
	{
		c = line[0][i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[0][i] && line[0][i] != c)
				i++;
		}
		else if (line[0][i] == '>' || line[0][i] == '<')
		{
			norme.j = i;
			if (help_to_parse(&line[0], norme, &(pi->pipe), &status[0]) == 0)
				return (0);
			i = 0;
		}
		if (line[0][i] != '\0')
			i++;
	}
	return (1);
}

char	*take_file(char **file, int *j)
{
	int		i;
	int		b;
	char	*line;

	while (file[0][*j] == ' ' || file[0][*j] == '\t' || file[0][*j] == '\n')
		(*j)++;
	i = *j;
	if (file[0][i] == '&')
		(*j) = help_to_take_file(*j, &file[0]);
	else
	{
		while (file[0][*j] != '\0' && file[0][*j] != ' ' && file[0][*j] != '\t'
			&& file[0][*j] != '\n' && file[0][*j] != '<' && file[0][*j] != '>')
			(*j)++;
	}
	b = (*j - i);
	line = ft_strsub(file[0], i, b);
	return (line);
}

void	join_with_anything(char **line, int a, int i)
{
	char	*first;
	char	*str;

	first = ft_strsub(*line, 0, i);
	str = ft_strdup(&line[0][a]);
	free(*line);
	line[0] = ft_strjoin(first, str);
	free(first);
	free(str);
}

int		type_pipe(char *line, int i)
{
	int type;

	if (line[i] == '>')
		type = 0;
	else if (line[i] == '<')
		type = 2;
	while (line[i] == '<' || line[i] == '>')
	{
		i++;
		type++;
	}
	return (type);
}

int		help_to_parse(char **line, t_fornorme norme, int ***pipe, int *status)
{
	int		out;
	int		type;
	char	*file;
	int		a;

	a = norme.j;
	type = type_pipe(line[0], norme.j);
	out = redirect_with_fd(line[0], &(norme.j));
	while (line[0][a] == '<' || line[0][a] == '>')
		a++;
	file = take_file(&line[0], &a);
	file = filter_for_file(file, norme.list);
	if (type == 4 && check_if_is_num(file) == 1 &&
		(line[0][a] == '<' || line[0][a] == '>'))
		return (print_error_num(file, pipe[0][2], &status[0]));
	if ((status[0] = parse_to_two(file, out, type, &pipe[0])) == 0)
		return (0);
	join_with_anything(&line[0], a, norme.j);
	free(file);
	return (1);
}
