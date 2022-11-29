/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:52:07 by hiantrin          #+#    #+#             */
/*   Updated: 2020/12/03 18:43:27 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*to_move_s_q(char **str, char c, int *start, int *end)
{
	start[0] = start[0] + 1;
	while (str[0][start[0]] && str[0][start[0]] != c)
	{
		if (str[0][start[0]] == 92 && c == 34)
			start[0] = start[0] + 2;
		else
			start[0] = start[0] + 1;
	}
	start[0] = start[0] + 1;
	str[0] = replace_by_s_q(str[0], &start[0], &end[0], 1);
	return (str[0]);
}

void	another_help_f_s_q(int *start, int *type)
{
	start[0] = start[0] + 2;
	type[0] = 0;
}

int		while_for_q_s(char **str)
{
	int fi;

	fi = 0;
	str[0] = ft_filter_quote(str[0], 0, &fi, 0);
	if (str[0] == NULL)
		return (0);
	if (fi == -1)
		return (-1);
	if ((fi = check_cursh(&str[0], 0, 'a', 0)) == -1)
		return (-1);
	if (fi == 0)
		return (0);
	return (check_parenthesis(&str[0]));
}

int		checker_for_anycurch(char *str)
{
	int		i;
	int		c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
			i = count_replace_env(str, i, c);
		else if (str[i] == 92)
			i++;
		else if (str[i] == '$' && (str[i + 1] == '{' || str[i + 1] == '('))
			i = jump_cursh_parent(str, i);
		else if (c == '{' || c == '}')
			return (print_error_parenthesis(str, c, i));
		if (str[i] != '\0')
			i++;
	}
	return (1);
}

int		norme_h_c_f_r_s(char *str, int *i, int *j)
{
	i[0] = jump_re_forsub(str, i[0]);
	j[0] = i[0];
	return (0);
}
