/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_alias_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:14:03 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/03 17:27:31 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_alloc_alias_node(t_alias **alias)
{
	*alias = (t_alias *)malloc(sizeof(t_alias));
	(*alias)->next = NULL;
	(*alias)->alias = NULL;
	(*alias)->value = NULL;
}
