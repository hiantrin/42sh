/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:37:27 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/03 18:52:57 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_print_one_alias(char *alias, t_alias *g_alias, t_process *p)
{
	int			flag;

	flag = 0;
	while (g_alias)
	{
		if (!ft_strcmp(g_alias->alias, alias))
		{
			ft_putstr_fd("alias ", p->output);
			ft_put3str_fd(g_alias->alias, "=", g_alias->value, p->output);
			ft_putchar_fd('\n', p->output);
			flag = 1;
		}
		g_alias = g_alias->next;
	}
	if (!flag)
	{
		g_the_status = 1;
		ft_put3str_fd("42sh: alias: ", alias, ": not found\n", p->errorput);
	}
	else
		g_the_status = 0;
}

int				ft_tab_len(char **args)
{
	int			i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int				ft_replace_alias_value(t_alias **h, char **cmd)
{
	t_alias		*head;

	head = *h;
	if (head && !head->next && !ft_strcmp(cmd[0], head->alias))
	{
		ft_strdel(&head->value);
		head->value = ft_strdup(cmd[1]);
		ft_free_tab(cmd);
		return (1);
	}
	while (head)
	{
		if (!ft_strcmp(cmd[0], head->alias))
		{
			ft_strdel(&head->value);
			head->value = ft_strdup(cmd[1]);
			ft_free_tab(cmd);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void			ft_set_alias(char *cmd, t_alias **g_alias)
{
	char		**split_cmd;
	t_alias		*head;

	if (!(split_cmd = ft_strsplit(cmd, '=')))
		return ;
	if (!*g_alias)
	{
		ft_alloc_alias_node(g_alias);
		(*g_alias)->alias = ft_strdup(split_cmd[0]);
		(*g_alias)->value = ft_strdup(split_cmd[1]);
		ft_free_tab(split_cmd);
		return ;
	}
	head = *g_alias;
	if (ft_replace_alias_value(&head, split_cmd))
		return ;
	while (head && head->next)
		head = head->next;
	ft_alloc_alias_node(&head->next);
	head = head->next;
	head->alias = ft_strdup(split_cmd[0]);
	head->value = ft_strdup(split_cmd[1]);
	ft_free_tab(split_cmd);
}

void			ft_alias(char **args, t_alias **g_alias, t_process *process)
{
	int			i;

	i = 0;
	if (ft_tab_len(args) == 1)
		ft_print_aliases(*g_alias, process);
	else
	{
		while (args[++i])
		{
			if (ft_strchr(args[i], '='))
			{
				if (args[i][0] == '-' || args[i][0] == '-' ||
				args[i][0] == '=' || args[i][0] == '/')
				{
					ft_put3str_fd("42sh: alias: ", args[i],
					": invalid input\n", process->errorput);
					g_the_status = 1;
				}
				else
					ft_set_alias(args[i], g_alias);
			}
			else
				ft_print_one_alias(args[i], *g_alias, process);
		}
	}
}
