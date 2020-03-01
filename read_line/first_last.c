/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:09:54 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/05 16:23:18 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		last_newline(t_key *key)
{
	if (key->line[key->position] == '\n'
			|| key->position != ft_strlen(key->line))
	{
		cursor_r(key);
		key = key_last_modification(NULL);
	}
	if (key->last && key->line)
		while (key->line[key->position])
		{
			if (!key->position || key->line[key->position] == '\n')
				break ;
			cursor_r(key);
			key = key_last_modification(NULL);
		}
	key_last_modification(key);
	return ;
}

void		first_newline(t_key *key)
{
	if (!key->line_x || key->position == ft_strlen(key->line))
	{
		cursor_le(key);
		key = key_last_modification(NULL);
	}
	if (key->first && key->line)
		while (key->line[key->position])
		{
			if ((!key->line_x && key->line[key->position - 1] == '\n')
					|| !key->position)
				break ;
			cursor_le(key);
			key = key_last_modification(NULL);
		}
	key_last_modification(key);
	return ;
}

void		first_last_line(t_key *key)
{
	if (ft_strchr(key->line, '\n') && key->first)
		return (first_newline(key));
	if (ft_strchr(key->line, '\n') && key->last)
		return (last_newline(key));
	if (key->first && key->line)
	{
		ft_putstr(tgoto(tgetstr("cm", NULL), key->first_x, key->first_y));
		key->position = 0;
		key->x = key->first_x;
		key->y = key->first_y;
	}
	else if (key->last && key->line)
	{
		ft_putstr(tgoto(tgetstr("cm", NULL), key->max_x, key->max_y));
		key->position = (!key->line) ? 0 : ft_strlen(key->line);
		key->x = key->max_x;
		key->y = key->max_y;
	}
	key_last_modification(key);
}
