/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_trait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 06:06:11 by hiantrin          #+#    #+#             */
/*   Updated: 2020/12/03 18:28:58 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	trait_that_final(char *str, t_process **process, t_job **job)
{
	pid_t		pid;

	g_if_sub = 2;
	pid = fork();
	if (pid == 0)
	{
		help_execve_help(&job[0], &process[0]);
		semicolon_parse(ft_strdup(str));
		exit(0);
	}
	else
	{
		process[0]->pid = pid;
		if (job[0]->pgid > 0)
			setpgid(pid, job[0]->pgid);
		else
		{
			job[0]->pgid = pid;
			setpgid(pid, job[0]->pgid);
		}
	}
	g_if_sub = 0;
}

void	onere_to_twore(char **str, int i)
{
	char	*tmp;
	char	*j;
	char	*tmp2;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '>' && str[0][i + 1] && str[0][i + 1] != '>')
		{
			j = ft_strsub(str[0], 0, i + 1);
			tmp2 = j;
			j = ft_strjoin(j, ">");
			free(tmp2);
			tmp = str[0];
			tmp2 = ft_strsub(str[0], i + 1, ft_strlen(str[0]) - (i + 1));
			str[0] = ft_strjoin(j, tmp2);
			free(tmp);
			free(tmp2);
			free(j);
			i = -1;
		}
		else if (str[0][i] == '>' && str[0][i + 1] && str[0][i + 1] == '>')
			i++;
		i++;
	}
}

char	*norme_final_trait(char *str)
{
	char	*new;

	new = ft_strdup(str);
	if (search_no_espace(new) == 0)
	{
		free(new);
		new = NULL;
	}
	else
		onere_to_twore(&new, 0);
	return (new);
}

int		final_trait(char *str, t_process **process, t_job **job)
{
	int		i;
	char	*new;
	char	*re;
	int		j;

	i = 0;
	if (norme_final_trat_v2(str, &i, &j) == 0)
		return (0);
	new = ft_strsub(str, j, i - j);
	re = ft_strsub(str, (i + 1), ft_strlen(str) - (i + 1));
	g_re.input = process[0]->input;
	g_re.output = process[0]->output;
	g_re.redirect = norme_final_trait(re);
	trait_that_final(new, &process[0], &job[0]);
	if (new != NULL)
		free(new);
	if (re != NULL)
		free(re);
	re = NULL;
	return (1);
}

char	*make_sub_happen(char *str, t_process **process)
{
	char	*new;
	char	*tmp;

	process[0]->output = g_re.output;
	if (g_re.redirect == NULL)
		return (str);
	new = ft_strjoin(g_re.redirect, " ");
	tmp = new;
	new = ft_strjoin(new, str);
	free(tmp);
	free(str);
	return (new);
}
