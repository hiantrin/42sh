/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_aliases_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:12:21 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/03 17:27:49 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_free_aliases_list(t_alias **aliases)
{
	t_alias		*nd;
	t_alias		*tmp;

	nd = *aliases;
	while (nd)
	{
		tmp = nd;
		nd = nd->next;
		ft_strdel(&tmp->alias);
		ft_strdel(&tmp->value);
		ft_memdel((void**)tmp);
	}
}
