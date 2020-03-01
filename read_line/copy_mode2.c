/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_mode2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:19:13 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:22:30 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		*all_right(t_key *key)
{
	while (key->position != key->copy1 + 1 && key->line[key->position])
	{
		cursor_r(key);
		key = key_last_modification(NULL);
	}
	return (key);
}

void		delete_select(t_key *key)
{
	int c;

	if (key->copy1 == key->copy2)
		return ;
	return_position_cursor(key, 0);
	clean(key);
	ft_putstr(key->line);
	return_position_cursor(key, 1);
	c = key->copy2 > key->copy1 ?
		key->copy2 - key->copy1 : key->copy1 - key->copy2 + 1;
	if (key->copy1 > key->copy2)
		key = all_right(key);
	while (c)
	{
		delete_char(key);
		key = key_last_modification(NULL);
		c--;
	}
}

void		past_select(t_key *key)
{
	char *p;

	p = NULL;
	return_position_cursor(key, 0);
	clean(key);
	ft_putstr(key->line);
	return_position_cursor(key, 1);
	p = key->copy1 > key->copy2 ?
		ft_strsub(key->line, key->copy2, (key->copy1 - key->copy2))
		: ft_strsub(key->line, key->copy1, (key->copy2 - key->copy1));
	while (1)
	{
		key = keybord_active(key);
		if (key->left || key->right)
			save_position(key, 0);
		if (key->alt_v)
		{
			key->lastread = p;
			if (key->lastread)
				plus_center_char(key);
			return ;
		}
	}
}
