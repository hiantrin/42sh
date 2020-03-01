/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:00:26 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/15 15:49:39 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		affichage_myenv(t_list *list, t_pi pi)
{
	list->first = list;
	if (pi.pipe[1][1] != -1)
	{
		while (list->first)
		{
			if (pi.pipe[1][1] != 0)
				ft_putendl_fd(list->first->str, pi.pipe[1][1]);
			list->first = list->first->next;
		}
	}
}

t_list		*ft_myshell(char **argv, int com, t_list *list, t_status *status)
{
	int	len;
	int	st;

	st = 1;
	len = 0;
	while (argv[len])
		len++;
	if (com == 1)
		mini_echo(argv, status->pi);
	else if (com == 2)
		list = mini_cd(argv, list, status->pi, &st);
	else if (com == 3 && status->pi.new == NULL)
		list = my_setenv(argv, list, status->pi);
	else if (com == 4 && status->pi.new == NULL)
		list = my_unsetenv(argv, list, len);
	else if (com == 5)
		affichage_myenv(list, status->pi);
	else if (com == 6)
		mini_type(argv, status->pi, list, &st);
	status->status = st;
	return (list);
}
