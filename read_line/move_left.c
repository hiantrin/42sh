/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:20:51 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 23:23:21 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			help_first_line(char *line, int len)
{
	struct winsize	term;
	int				i;

	i = 0;
	ioctl(1, TIOCGWINSZ, &term);
	while (line[i] && line[i] != '\n')
		i++;
	if ((i + 6) >= term.ws_col - 1 && len <= i)
		i = 6;
	else
		i = 0;
	return (i);
}

int			line_size_up(int len, char *line)
{
	struct winsize	term;
	int				x;
	int				i;

	x = 0;
	ioctl(1, TIOCGWINSZ, &term);
	i = help_first_line(line, len);
	len--;
	while (len >= 0)
	{
		if (line[len] == '\n')
			break ;
		len--;
	}
	len++;
	if (len == -1)
		len = 0;
	while (len >= 0 && line[len])
	{
		if (len > 0 && line[len] == '\n')
			return ((x + i) % term.ws_col);
		len++;
		x++;
	}
	return (x);
}

t_key		*left_newline(t_key *key)
{
	struct winsize	term;

	ioctl(1, TIOCGWINSZ, &term);
	if (!key->line_x && key->line_y > key->first_y)
	{
		key->x--;
		key->line_y--;
		if (key->line[key->position - 1] == '\n')
			key->line_x = line_size_up((key->position - 1), key->line);
		else
			key->line_x = term.ws_col - 1;
		if (key->first_y == key->line_y && key->line_x != term.ws_col - 1)
			key->line_x += key->size;
	}
	else if ((key->line_y == key->first_y && key->position)
			|| key->line_y > key->first_y)
	{
		key->line_x--;
		key->x--;
	}
	ft_putstr(tgoto(tgetstr("cm", NULL), key->line_x, key->line_y));
	return (key);
}

void		cursor_le(t_key *key)
{
	struct winsize	term;

	ioctl(1, TIOCGWINSZ, &term);
	key->change = key->x;
	if (key->line && ft_strchr(key->line, '\n'))
		key = left_newline(key);
	else if (key->y > key->first_y)
	{
		if (!key->x)
		{
			key->y--;
			key->x = term.ws_col - 1;
		}
		else
			key->x--;
		ft_putstr(tgoto(tgetstr("cm", NULL), key->x, key->y));
	}
	else if (key->y == key->first_y && key->x > key->first_x)
	{
		key->x--;
		ft_putstr(tgoto(tgetstr("cm", NULL), key->x, key->y));
	}
	if (key->change != key->x)
		key->position--;
	key_last_modification(key);
}
