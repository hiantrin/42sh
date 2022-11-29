/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:43:18 by hiantrin          #+#    #+#             */
/*   Updated: 2020/12/03 15:57:33 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	norme_make_another_and_kill(t_save save)
{
	g_fi = save.fi;
	g_shell = save.shell;
	g_status_string = save.status_string;
	g_semicolon = save.semicolon;
	g_and_and = save.and_and;
	g_or_or = save.or_or;
	g_the_jobs = save.the_jobs;
	g_the_status = save.the_status;
	g_if_exit = save.if_exit;
}

int		free_and_error(char *tmp)
{
	free(tmp);
	ft_putendl_fd("bash: syntax error near unexpected token `)'", 2);
	return (0);
}

int		norme_read_the_parent(char *str, int i, int *j, char *b)
{
	j[0] = i;
	b[0] = str[i];
	return (1);
}

int		return_i_or_s(char *str, int i, int s)
{
	if (str[i] == ')')
		return (i);
	if (checker_for_braces_checker(str, i, s) == 1)
		return (i);
	else
		return (s);
}

int		return_s(char *tmp, int s)
{
	free(tmp);
	return (s);
}
