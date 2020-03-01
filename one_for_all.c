/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_for_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:25:32 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	anathor_help_for_mini1(char *str, t_norme3 *norme3, t_norme2 *norme)
{
	norme->str = ft_strdup(str);
	norme->tab = norme3->str;
	norme->status = 2;
	norme->andand = norme3->andand;
	norme->oror = norme3->oror;
}

void	another_mini_help_for_mini2(t_status *status, char *commande)
{
	ft_putstr_fd("42sh: command not found: ", status->pi.pipe[2][1]);
	ft_putendl_fd(commande, status->pi.pipe[2][1]);
	status->status = 0;
}

int		check_if_and_and(char **str, int i)
{
	while (1)
	{
		i = 0;
		if (!str[0] || check_count_and(str[0], 0) == 0)
			return (0);
		while (str[0][i])
			i++;
		i--;
		if (i == 0)
			break ;
		while (i != 0)
		{
			if (str[0][i] != ' ' && str[0][i] != '\t' && str[0][i] != '\n'
				&& str[0][i] != '&' && str[0][i] != '|')
				return (1);
			else if (str[0][i] == '|' || str[0][i] == '&')
			{
				help_to_finish_the_pipe(&str[0]);
				break ;
			}
			i--;
		}
	}
	return (1);
}

int		check_count_and(char *str, int count)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		c = str[i];
		if (c == 34 || c == 39)
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == '|' || str[i] == '&' || str[i] == '|'
			|| str[i] == '>' || str[i] == '<' || str[i] == ';')
		{
			if (some_name(&i, &j, str, c) == 0)
				return (0);
		}
		if (str[i] != '\0')
			i++;
	}
	return (some_norme_again(str, j, c, count));
}

int		some_norme_again(char *str, int j, char c, int count)
{
	if ((str[j] == '\0' || search_no_espace(&str[j]) == 0) &&
		(str[j - 1] == '<' || str[j - 1] == '>' ||
		(str[j - 1] == '&' && (str[j - 2] == '>' || str[j - 2] == '<'))))
		return (print_and_of_number(c, count));
	return (1);
}
