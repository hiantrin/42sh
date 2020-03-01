/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_up_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:15:02 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:16:39 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		alt_down(t_key *key, int historique_x, int historique_y)
{
	if (historique_y == key->first_y)
		historique_x -= key->size;
	while (1)
	{
		if (historique_y < key->line_y && historique_x <= key->line_x)
			break ;
		cursor_r(key);
		key = key_last_modification(NULL);
	}
}

void		alt_up_down(t_key *key)
{
	int historique_x;
	int historique_y;

	historique_x = key->line_x;
	historique_y = key->line_y;
	if (key->alt_up && historique_y - 1 == key->first_y)
		historique_x += key->size;
	if (key->alt_down && key->line_max > key->line_y)
		alt_down(key, historique_x, historique_y);
	else if (key->alt_up && key->first_y < key->line_y)
	{
		while (1)
		{
			if (historique_y > key->line_y && historique_x >= key->line_x)
				break ;
			cursor_le(key);
			key = key_last_modification(NULL);
		}
	}
}
