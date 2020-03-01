/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 19:16:59 by hiantrin          #+#    #+#             */
/*   Updated: 2020/01/17 12:51:14 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*move_slash(char *line)
{
	char	*str;
	int		a;

	a = count_slash(line);
	if (a != 0)
	{
		str = help_slash(line, a);
		free(line);
		return (str);
	}
	return (line);
}

char	*help_slash(char *line, int a)
{
	char	*str;
	int		j;
	char	c;

	str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1 - a));
	str[ft_strlen(line) - a] = '\0';
	j = 0;
	a = 0;
	while (line[j])
	{
		c = line[j];
		if (c == 34 || c == 39)
		{
			j++;
			while (line[j] && line[j] != c)
				j++;
		}
		else if (c != 92)
			str[a++] = line[j];
		if (line[j] != '\0')
			j++;
	}
	return (str);
}

int		count_slash(char *line)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (line[i] && line[i] != c)
				i++;
		}
		else if (c == 92)
			count++;
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

char	*move_quote(char *line, int i)
{
	char	c;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (line[i])
	{
		c = line[i];
		if (c == 34 || c == 39)
		{
			j = i;
			i++;
			while (line[i] != c)
				i++;
			str = ft_strsub(line, j + 1, (i - (j + 1)));
			join_with_something(&line, str, i + 1, j);
			i--;
		}
		else
			i++;
	}
	return (line);
}
