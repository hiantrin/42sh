/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:23:04 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 21:26:03 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		return_cursor(t_key *key, int position_cursor)
{
	while (position_cursor)
	{
		cursor_le(key);
		key = key_last_modification(NULL);
		position_cursor--;
	}
}

int			delete_center_char(t_key *key)
{
	struct winsize	term;
	int				position_cursor;
	char			*tmp;
	int				i;
	int				j;

	ioctl(1, TIOCGWINSZ, &term);
	position_cursor = key->position;
	tmp = key->line;
	key->line = ft_strnew(ft_strlen(key->line) - 1);
	j = 0;
	i = 0;
	while (tmp[j])
	{
		if (j != position_cursor - 1)
			key->line[i++] = tmp[j];
		j++;
	}
	key->line[i] = '\0';
	clean_last_line(key);
	return_cursor(key, (ft_strlen(tmp) - position_cursor));
	free(tmp);
	return (1337);
}

void		delete_char(t_key *key)
{
	struct winsize	term;
	char			*tmp;

	ioctl(1, TIOCGWINSZ, &term);
	if (!key->line || !key->position)
		return ;
	if (ft_strlen(key->line) != key->position && delete_center_char(key))
		return ;
	if (ft_strlen(key->line) == 1)
	{
		free(key->line);
		key->line = NULL;
		key->x = 0;
		clean(key);
		key_last_modification(key);
		return ;
	}
	tmp = key->line;
	key->line = ft_strsub(key->line, 0, ft_strlen(key->line) - 1);
	free(tmp);
	clean_last_line(key);
	key = key_last_modification(NULL);
	key_last_modification(key);
}
