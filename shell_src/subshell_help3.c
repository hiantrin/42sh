/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_help3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 02:16:39 by hiantrin          #+#    #+#             */
/*   Updated: 2020/12/03 17:41:59 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*read_the_sub(char *str, int j, int i)
{
	char	*tmp;
	int		a;
	char	*new;

	a = 0;
	new = NULL;
	while (!a || search_no_espace(new) == 0)
	{
		a = 1;
		if (new != NULL)
			free(new);
		new = my_readline(&g_his, "> ");
	}
	if (new == NULL)
		return (NULL);
	tmp = ft_strsub(str, j, i - j);
	if (search_no_espace(tmp) == 0)
		str = ft_strjoin(str, " ");
	else
		str = ft_strjoin(str, "; ");
	free(tmp);
	tmp = str;
	str = ft_strjoin(str, new);
	free(tmp);
	return (str);
}

int		cursh_read_e(char *str, int j)
{
	char	*tmp;

	if (j == 0)
		return (1);
	tmp = ft_strsub(str, 0, j);
	if (search_no_espace(tmp) == 0)
	{
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

int		return_read_the_parent(char **str, int i, int j, int a)
{
	char	*tmp;

	if (a == 1 && (str[0][j] == '(' ||
		(str[0][j] == '{' && cursh_read_e(str[0], j) == 1)))
	{
		tmp = str[0];
		str[0] = read_the_sub(str[0], j + 1, i);
		free(tmp);
		if (str[0] == NULL)
			return (0);
		return (-1);
	}
	return (1);
}

int		read_the_parent(char **str, int a, int i, int j)
{
	char	c;
	char	b;

	while (str[0][i])
	{
		c = str[0][i];
		if (c == 34 || c == 39)
			i = count_replace_env(str[0], i, c);
		else if (str[0][i] == 92)
			i++;
		else if (str[0][i] == '$' && (str[0][i + 1] == '{'
			|| str[0][i + 1] == '('))
			i = jump_cursh_parent(str[0], i);
		else if ((str[0][i] == '(' || str[0][i] == '{') && a == 0)
			a = norme_read_the_parent(str[0], i, &j, &b);
		else if (a == 1 && ((b == '(' && str[0][i] == ')') ||
			(b == '{' && str[0][i] == '}')))
			a = 0;
		if (str[0][i] != '\0')
			i++;
	}
	return (return_read_the_parent(&str[0], i, j, a));
}

void	second_loop_sub(char **str)
{
	int a;

	a = -1;
	while (a == -1)
		a = read_the_parent(&str[0], 0, 0, 0);
}
