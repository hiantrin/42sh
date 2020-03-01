/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:06:28 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:10:05 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key		*cursor_first_pos(t_key *key)
{
	char	posetion[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(posetion, 20);
	i = read(0, posetion, 20);
	posetion[i] = 0;
	i = 2;
	key->first_y = ft_atoi(posetion + i) - 1;
	while (ft_isdigit(posetion[i]))
		i++;
	key->first_x = ft_atoi(posetion + i + 1) - 1;
	return (key);
}

void		clean(t_key *key)
{
	ft_putstr(tgoto(tgetstr("cm", NULL), 0, key->first_y));
	ft_putstr(key->path);
	ft_putstr(tgetstr("cd", NULL));
}

t_key		*put_line2(t_key *key, struct winsize term)
{
	if (!ft_strchr(key->line, '\n') && key->position + key->size
			- ((key->y - key->first_y) * term.ws_col) == term.ws_col)
	{
		key->y++;
		key->x = 0;
	}
	ft_putchar(key->line[key->position]);
	key->position++;
	key->x++;
	return (key);
}

t_key		*last_char(t_key *key, struct winsize term)
{
	int line;

	if (!ft_strchr(key->line, '\n') && key->y > term.ws_row - 1)
	{
		line = key->y - (term.ws_row - 1);
		key->first_y = (key->first_y - line < 0) ? 0 : key->first_y - line;
		key->y = term.ws_row - 1;
	}
	else if (ft_strchr(key->line, '\n') && key->line_y > term.ws_row - 1)
	{
		line = key->line_y - (term.ws_row - 1);
		key->first_y = (key->first_y - line < 0) ? 0 : key->first_y - line;
		key->line_y = term.ws_row - 1;
	}
	return (key);
}

void		clean_last_line(t_key *key)
{
	struct winsize	term;

	clean(key);
	key_last_modification(key);
	if (!key->line)
		return ;
	key->x = key->first_x;
	key->y = key->first_y;
	ioctl(1, TIOCGWINSZ, &term);
	key->position = 0;
	while (key->line[key->position])
		key = put_line2(key, term);
	if (!(ft_strchr(key->line, '\n')))
		key = last_char(key, term);
	key->max_x = key->x;
	key->max_y = key->y;
	key->line_x = len_lastline(key->line);
	key->line_y = key->first_y + cont_newline(key->line);
	if (ft_strchr(key->line, '\n'))
		key = last_char(key, term);
	key->line_max = key->line_y;
	key_last_modification(key);
}
