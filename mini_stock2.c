/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_stock2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:55:46 by szakaria          #+#    #+#             */
/*   Updated: 2020/01/17 12:49:42 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			my_magic2(t_list *list)
{
	int	cont;

	cont = 0;
	list->first = list;
	while (list->first)
	{
		cont++;
		list->first = list->first->next;
	}
	return (cont);
}

char		**my_magic(t_list *list)
{
	char	**env;
	int		i;

	env = (char **)malloc(sizeof(char *) * my_magic2(list) + 1);
	env[my_magic2(list)] = NULL;
	list->first = list;
	i = 0;
	while (list->first)
	{
		env[i] = list->first->str;
		list->first = list->first->next;
		i++;
	}
	return (env);
}
