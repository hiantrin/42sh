/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:49:52 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/02 20:53:35 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

void			ft_free_matches_lst(t_dlist **n)
{
	t_dlist		*nd;
	t_dlist		*tmp;

	nd = *n;
	while (nd)
	{
		tmp = nd;
		nd = nd->next;
		ft_strdel(&tmp->data);
		free(tmp);
	}
}

void			ft_alloc_node(t_dlist **node)
{
	*node = (t_dlist *)malloc(sizeof(t_dlist));
	(*node)->next = NULL;
	(*node)->data = NULL;
}
