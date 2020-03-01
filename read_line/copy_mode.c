/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:17:01 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:18:27 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int g_x;
static int g_y;

void		aff_last_modification(char *line, int copy1, int copy2)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((i >= copy1 && i <= copy2) || (i >= copy2 && i <= copy1))
			ft_putstr(tgetstr("us", NULL));
		ft_putchar(line[i]);
		ft_putstr(tgetstr("me", NULL));
		i++;
	}
}

t_key		*return_position_cursorv2(t_key *key, int mode)
{
	if (mode && ft_strchr(key->line, '\n'))
	{
		key->line_x = g_x;
		key->line_y = g_y;
		ft_putstr(tgoto(tgetstr("cm", NULL), g_x, g_y));
	}
	else if (mode)
	{
		key->x = g_x;
		key->y = g_y;
		ft_putstr(tgoto(tgetstr("cm", NULL), g_x, g_y));
	}
	return (key);
}

t_key		*return_position_cursor(t_key *key, int mode)
{
	if (!mode && ft_strchr(key->line, '\n'))
	{
		g_x = key->line_x;
		g_y = key->line_y;
	}
	else if (!mode)
	{
		g_x = key->x;
		g_y = key->y;
	}
	if (mode)
		return (return_position_cursorv2(key, mode));
	return (key);
}

t_key		*save_position(t_key *key, int per)
{
	if (key->left)
	{
		cursor_le(key);
		key = key_last_modification(NULL);
		key->copy2 = key->position;
	}
	if (key->right)
	{
		cursor_r(key);
		key = key_last_modification(NULL);
		key->copy2 = key->position;
	}
	key_last_modification(key);
	if (!per)
		return (key);
	return_position_cursor(key, 0);
	clean(key);
	aff_last_modification(key->line, key->copy1, key->copy2);
	key = return_position_cursor(key, 1);
	return (key);
}

void		mode_copy(t_key *key)
{
	key->alt_c = 0;
	key->alt_x = 0;
	key->copy1 = key->position;
	key->copy2 = key->position;
	while (1)
	{
		key = keybord_active(key);
		if (key->left || key->right)
			key = save_position(key, 1);
		if (key->alt_x)
		{
			delete_select(key);
			key = key_last_modification(NULL);
			key->alt_x = 0;
			break ;
		}
		if (key->alt_c)
		{
			past_select(key);
			key = key_last_modification(NULL);
			key->alt_c = 0;
			break ;
		}
		key_last_modification(key);
	}
}
