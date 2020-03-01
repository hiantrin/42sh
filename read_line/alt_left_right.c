/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:10:30 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:14:39 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		alt_left(t_key *key)
{
	if (key->alt_left && key->position)
	{
		while (key->position && !ft_isalnum(key->line[key->position - 1]))
		{
			cursor_le(key);
			key = key_last_modification(NULL);
		}
		while (key->position)
		{
			if (!key->position || (key->position &&
						!ft_isalnum(key->line[key->position - 1])))
			{
				key_last_modification(key);
				return ;
			}
			cursor_le(key);
			key = key_last_modification(NULL);
		}
		key_last_modification(key);
	}
}

void		alt_left_right(t_key *k)
{
	if (!k->line)
		return ;
	if (k->alt_left && k->position)
		alt_left(k);
	if (k->alt_right && k->position != ft_strlen(k->line))
	{
		while (k->position && !ft_isalnum(k->line[k->position - 1])
				&& ft_isalnum(k->line[k->position]))
		{
			cursor_r(k);
			k = key_last_modification(NULL);
		}
		while (k->line[k->position] && k->position <= ft_strlen(k->line))
		{
			if (k->position && !ft_isalnum(k->line[k->position - 1])
					&& ft_isalnum(k->line[k->position]))
			{
				key_last_modification(k);
				return ;
			}
			cursor_r(k);
			k = key_last_modification(NULL);
		}
		key_last_modification(k);
	}
}
