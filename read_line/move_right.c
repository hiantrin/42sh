/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:24:23 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 23:24:58 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key			*right_newline(t_key *key)
{
	struct winsize	term;

	ioctl(1, TIOCGWINSZ, &term);
	if (key->line[key->position] == '\n' || key->line_x == term.ws_col - 1)
	{
		key->line_x = 0;
		key->x++;
		key->line_y++;
	}
	else if (key->x < key->max_x)
	{
		key->line_x++;
		key->x++;
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), key->line_x, key->line_y));
	return (key);
}

void			cursor_r(t_key *k)
{
	struct winsize	term;

	k->change = k->x;
	ioctl(1, TIOCGWINSZ, &term);
	if (k->line && ft_strchr(k->line, '\n'))
		k = right_newline(k);
	else if (k->max_y >= k->first_y)
	{
		if (k->x == term.ws_col - 1)
		{
			k->y++;
			k->x = 0;
		}
		else if (k->position < ft_strlen(k->line))
			k->x++;
		ft_putstr(tgoto(tgetstr("cm", NULL), k->x, k->y));
	}
	else if (k->y == k->first_y && k->x >= k->first_x && k->position < k->size)
	{
		k->x++;
		ft_putstr(tgoto(tgetstr("cm", NULL), k->x, k->y));
	}
	if (k->change != k->x)
		k->position++;
	key_last_modification(k);
}
