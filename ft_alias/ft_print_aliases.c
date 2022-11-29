/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_aliases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:18:23 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/03 17:29:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_print_aliases(t_alias *aliases, t_process *process)
{
	while (aliases)
	{
		ft_putstr_fd("alias ", process->output);
		ft_put3str_fd(aliases->alias, "=", aliases->value, process->output);
		ft_putchar_fd('\n', process->output);
		aliases = aliases->next;
	}
}
