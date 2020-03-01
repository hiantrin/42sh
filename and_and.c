/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 04:20:05 by hiantrin          #+#    #+#             */
/*   Updated: 2020/02/12 16:03:25 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_list	*or_or(t_list *list, char *str, t_norme3 *norme)
{
	char	**new;
	int		i;

	i = 0;
	new = split_and_and(str, '|');
	while (new[i])
	{
		norme->p0 = 0;
		norme->status = 2;
		norme->oror = new;
		if (check_line(new[i]) != 0)
		{
			if ((list = ft_trait0(list, new[i], &norme[0], -1)) == NULL)
				return (NULL);
			if (norme->status != 0)
			{
				norme->status2 = norme->status;
				free_2d(new);
				return (list);
			}
		}
		i++;
	}
	free_2d(new);
	return (list);
}

char	**split_and_and(char *line, char c)
{
	char	**command;
	int		count;

	count = count_and_and(line, c);
	command = (char **)malloc(sizeof(char *) * count + 1);
	command[count] = NULL;
	help_split_and_and(line, command, 0, c);
	return (command);
}

void	help_split_and_and(char *line, char **command, int i, char s)
{
	char	c;
	int		j;
	int		a;

	a = 0;
	j = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
		{
			command[a++] = ft_strsub(line, j, i - j);
			i++;
			j = i + 1;
		}
		if (line[i] != '\0')
			i++;
	}
	command[a] = ft_strsub(line, j, i - j);
}

int		count_and_and(char *line, char s)
{
	int		i;
	int		count;
	char	c;

	count = 1;
	i = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[i] != c)
				i++;
		}
		else if (c == s && line[i + 1] == s && line[i + 2] != s)
		{
			count++;
			i++;
		}
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

t_list	*and_and(t_list *list, char *str, t_norme3 norme)
{
	char	**new;
	int		i;

	i = 0;
	new = split_and_and(str, '&');
	while (new[i])
	{
		norme.andand = new;
		norme.status2 = 1;
		if (check_line(new[i]) != 0)
		{
			if ((list = or_or(list, new[i], &norme)) == NULL)
				return (NULL);
			if (norme.status2 == 0)
			{
				free_2d(new);
				return (list);
			}
		}
		i++;
	}
	free_2d(new);
	return (list);
}
