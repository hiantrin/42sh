/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 02:22:30 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/15 15:33:31 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_list		*my_setenv2(char **argv, t_list *list)
{
	char	*new;

	new = NULL;
	list->first = list;
	while (list->first->next)
		list->first = list->first->next;
	list->first->next = new_list("vide");
	list->first = list->first->next;
	ft_memdel(&list->first->str);
	new = ft_strjoin(argv[1], "=");
	if (argv[2] != NULL)
	{
		list->first->str = ft_strjoin(new, argv[2]);
		ft_memdel(&new);
	}
	else
		list->first->str = new;
	return (list);
}

int			mylen2(char *str, char *argv)
{
	if (str != NULL && argv == NULL)
		return (ft_strlen(str));
	if (argv != NULL && str == NULL)
		return (ft_strlen(argv));
	if (mylen(str) > (int)ft_strlen(argv))
		return (mylen(str));
	return (ft_strlen(argv));
}

t_list		*my_setenv2v2(char **argv, t_list *list, char *new)
{
	ft_memdel(&list->first->str);
	new = ft_strjoin(argv[1], "=");
	if (argv[2] != NULL)
	{
		list->first->str = ft_strjoin(new, argv[2]);
		ft_memdel(&new);
	}
	else
		list->first->str = new;
	return (list);
}

t_list		*my_setenv(char **argv, t_list *list, t_pi pi)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	list->first = list;
	if (tarit_my_setnv(argv, list, pi))
		while (list->first)
		{
			if (ft_strncmp(list->first->str, argv[1]
						, mylen2(list->first->str, argv[1])) == 0)
				return (my_setenv2v2(argv, list, new));
			list->first = list->first->next;
		}
	else
		return (list);
	return (my_setenv2(argv, list));
}
