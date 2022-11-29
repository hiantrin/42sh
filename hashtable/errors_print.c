/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 06:11:13 by ysarsar           #+#    #+#             */
/*   Updated: 2020/12/02 18:23:27 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_hash_error(char *str, t_process *process)
{
	if (str)
	{
		ft_putstr_fd("42sh: hash: ", process->errorput);
		ft_putstr_fd(str, process->errorput);
		ft_putendl_fd(": invalid option", process->errorput);
		ft_putstr_fd("42sh: usage: ", process->errorput);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]",
						process->errorput);
	}
	else
	{
		ft_putendl_fd("42sh: hash: -p: option requires an argument",
						process->errorput);
		ft_putstr_fd("42sh: usage: ", process->errorput);
		ft_putendl_fd("hash [-lr] [-p pathname] [-dt] [name ...]",
						process->errorput);
	}
}

void		l_flag_error(char *str, t_process *process)
{
	ft_putstr_fd("42sh: hash: ", process->errorput);
	ft_putstr_fd(str, process->errorput);
	ft_putstr_fd(": not found\n", process->errorput);
}

void		l_flag_print(char *value, char *key, t_process *process)
{
	ft_putstr_fd("builtin hash -p ", process->output);
	ft_putstr_fd(value, process->output);
	ft_putchar_fd(' ', process->output);
	ft_putendl_fd(key, process->output);
}

char		*absolute_path(char *path, char *command)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(path, "/");
	str2 = ft_strjoin(str1, command);
	ft_strdel(&str1);
	return (str2);
}
