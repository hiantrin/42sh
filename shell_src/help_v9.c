/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_v9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:41:29 by hiantrin          #+#    #+#             */
/*   Updated: 2020/12/03 17:15:12 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		braces_checker(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '{' && str[i + 1] == ' ')
	{
		i = 2;
		while (str[i] && str[i] != '}')
		{
			if (str[i] == '{' || str[i] == '(' || str[i] == ')')
				return (0);
			i++;
		}
		if (str[i--] == '}')
		{
			while ((str[i] == ' ' || str[i] == '\t') && i > 0)
				i--;
			return (str[i] == ';' ? 1 : 0);
		}
		return (0);
	}
	return (0);
}

int		checker_for_braces_checker(char *str, int i, int j)
{
	char *tmp;

	tmp = ft_strsub(str, j, (i + 1) - j);
	if (braces_checker(tmp) == 1)
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

int		complete_get_command_type(char *command)
{
	if (ft_strcmp(command, "type") == 0)
		return (COMMAND_TYPE);
	else if (ft_strcmp(command, "env") == 0)
		return (COMMAND_ENV);
	else if (ft_strcmp(command, "alias") == 0)
		return (COMMAND_ALIAS);
	else if (ft_strcmp(command, "unalias") == 0)
		return (COMMAND_UNALIAS);
	else if (ft_strcmp(command, "test") == 0)
		return (COMMAND_TEST);
	else if (ft_strcmp(command, "hash") == 0)
		return (COMMAND_HASH);
	else
		return (COMMAND_EXTERNAL);
}

int		complete_trait_built(t_job *j, t_process *process)
{
	if (process->type == COMMAND_CD)
		to_cd(process, j);
	else if (process->type == COMMAND_ALIAS)
		ft_alias(process->argv, &g_alias, process);
	else if (process->type == COMMAND_UNALIAS)
		ft_unalias(process->argv, &g_alias, process);
	else if (process->type == COMMAND_TEST)
		ft_test(process->argv, process);
	else if (process->type == COMMAND_HASH)
		ft_hash(process->argv, &g_hashtable, process);
	return (0);
}

int		norme_final_trat_v2(char *str, int *i, int *j)
{
	char	a;

	while (str[i[0]] && (str[i[0]] == ' ' ||
		str[i[0]] == '\t' || str[i[0]] == '\n'))
		i[0] = i[0] + 1;
	if (str[i[0]] && str[i[0]] != '(' && str[i[0]] != '{')
		return (0);
	j[0] = i[0] + 1;
	if (str[i[0]] == '(')
		a = ')';
	else if (str[i[0]] == '{')
		a = '}';
	while (str[i[0]] && str[i[0]] != a)
		i[0] = i[0] + 1;
	if (a == '}' && checker_for_braces_checker(str, i[0], j[0] - 1) == 0)
		return (0);
	return (1);
}
