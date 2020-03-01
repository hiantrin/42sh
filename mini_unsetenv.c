/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 04:36:34 by szakaria          #+#    #+#             */
/*   Updated: 2020/01/17 12:50:01 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_list		*new_list(char *tmp)
{
	t_list *listnew;

	listnew = malloc(sizeof(t_list));
	listnew->str = ft_strdup(tmp);
	listnew->next = NULL;
	return (listnew);
}

t_list		*stock_list(char **env)
{
	t_list	*list;
	t_list	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (i == 0)
		{
			list = new_list(env[i]);
			tmp = list;
		}
		else
		{
			tmp->next = new_list(env[i]);
			tmp = tmp->next;
		}
		i++;
	}
	return (list);
}

int			mylen(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_list		*my_unsetenv2(char *argv, t_list *list)
{
	int		per;
	t_list	*tmp;

	per = 0;
	tmp = NULL;
	while (list)
	{
		if (per == 0)
			tmp = list;
		if (list->next)
			tmp = list->next;
		if (tmp && ft_strncmp(tmp->str, argv, mylen2(tmp->str, argv)) == 0)
		{
			if (tmp->next)
				list->next = tmp->next;
			else
				list->next = NULL;
			ft_memdel(&tmp->str);
			free(tmp);
		}
		list = list->next;
		per++;
	}
	return (list);
}

t_list		*my_unsetenv(char **argv, t_list *list, int len)
{
	int			i;
	t_list		*tmp;

	list->first = list;
	i = 1;
	tmp = NULL;
	if (len == 1)
	{
	}
	else
		while (argv[i])
		{
			list->first = list;
			if (ft_strncmp(list->first->str, argv[i],
						mylen2(list->first->str, argv[i])) == 0)
			{
				tmp = list->first;
				list->first = list->first->next;
				free(tmp);
				return (list->first);
			}
			list->first = my_unsetenv2(argv[i], list->first);
			i++;
		}
	return (list);
}
