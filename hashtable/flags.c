/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:15:49 by ysarsar           #+#    #+#             */
/*   Updated: 2020/12/02 18:23:59 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		l_flag(t_hash **h_table, char **args, t_process *process)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		c;
	int		slot;

	hashtable = *h_table;
	c = 1;
	slot = -1;
	while (args[++c])
	{
		slot = hash_function(args[c]);
		current = hashtable->list[slot];
		l_flag_mini(args[c], current, process);
	}
	l_flag_valid(hashtable, slot, process);
}

void		d_flag(t_hash **h_table, char **args, t_process *process)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		del_hash(h_table, args, process);
	else if (len == 2)
		aff_hashtable(h_table, process);
}

void		t_flag(t_hash **h_table, char **args, t_process *process)
{
	int		len;

	len = ft_argslen(args);
	if (len > 2)
		search_hash(h_table, args, len, process);
	else
		ft_putendl_fd("42sh: hash: -t: option requires an argument",
						process->errorput);
}

void		p_flag(t_hash **h_table, char **args, t_process *process)
{
	if (ft_argslen(args) == 2)
		ft_hash_error(NULL, process);
	else
		p_flag_mini(args, h_table, process);
}

void		search_hash(t_hash **h_table, char **args, int len,
						t_process *process)
{
	t_hash	*hashtable;
	t_ht	*current;
	int		slot;

	hashtable = *h_table;
	if (len == 3)
	{
		slot = hash_function(args[2]);
		current = hashtable->list[slot];
		if (!current)
			l_flag_error(args[2], process);
		while (current)
		{
			if (ft_strcmp(args[2], current->key) == 0)
			{
				ft_putendl_fd(current->value, process->output);
				break ;
			}
			current = current->next;
		}
	}
	else
		search_hash_mini(h_table, args, process);
}
