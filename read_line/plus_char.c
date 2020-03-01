/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:21:16 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/05 16:22:53 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char		*myjoin(char *line, char *lastread)
{
	char		*new;
	int			i;
	int			j;

	if (!line)
		line = ft_strnew(0);
	new = ft_strnew(ft_strlen(line) + ft_strlen(lastread) + 1);
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	j = 0;
	while (lastread[j])
		new[i++] = lastread[j++];
	free(line);
	return (new);
}

int			plus_center_char_v2(t_key *key, char *tmp, int position_cursor)
{
	clean_last_line(key);
	key = key_last_modification(NULL);
	return_cursor(key, (ft_strlen(tmp) - position_cursor));
	ft_memdel(&tmp);
	ft_memdel(&key->lastread);
	key_last_modification(key);
	return (1337);
}

int			plus_center_char(t_key *key)
{
	char			*tmp;
	int				i;
	int				j;
	int				position_cursor;
	struct winsize	term;

	ioctl(1, TIOCGWINSZ, &term);
	position_cursor = key->position;
	tmp = key->line;
	key->line = ft_strnew(ft_strlen(key->line) + ft_strlen(key->lastread));
	i = 0;
	j = 0;
	while (tmp[i] && i < position_cursor)
		key->line[j++] = tmp[i++];
	i = 0;
	while (key->lastread[i])
		key->line[j++] = key->lastread[i++];
	i = position_cursor;
	while (tmp[i])
		key->line[j++] = tmp[i++];
	key->line[j] = '\0';
	return (plus_center_char_v2(key, tmp, position_cursor));
}

void		plus_char(t_key *key)
{
	struct winsize	term;

	ioctl(1, TIOCGWINSZ, &term);
	key->size_last = !key->line ? 0 : ft_strlen(key->line);
	if (key->size_last &&
			key->size_last != key->position && plus_center_char(key))
		return ;
	key->line = myjoin(key->line, key->lastread);
	ft_memdel(&key->lastread);
	clean_last_line(key);
}
