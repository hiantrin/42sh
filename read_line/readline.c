/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:28:48 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/15 17:24:24 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key			*all(t_key *key, int first, int mode, char *path)
{
	ft_putstr(path);
	if (!first)
		manger_error();
	if (mode)
		change_configuration_term(1);
	else if (!mode)
		change_configuration_term(0);
	key = (t_key *)malloc(sizeof(t_key));
	key = cursor_first_pos(key);
	key->size = (!path) ? 0 : ft_strlen(path);
	key->path = (!path) ? NULL : path;
	key->line = NULL;
	key->all_commande = 0;
	key->max_x = 0;
	key->max_y = 0;
	return (key);
}

void			lance_signal(int signal)
{
	char buff[1];

	signal = 0;
	we_have_signal(1);
	buff[0] = 0;
	ioctl(1, TIOCSTI, buff);
}

char			*exit_readline(t_key *key, int mode)
{
	char	*line;

	change_configuration_term(0);
	if (mode == 1)
		line = (!ft_strcmp("herdoc> ", key->path)) ? NULL : ft_strdup("exit");
	else if (mode == 3)
		line = NULL;
	else if (key->line)
		line = ft_strdup(key->line);
	else
		line = ft_strnew(0);
	if (key->line && ft_strchr(key->line, '\n'))
		ft_putstr(tgoto(tgetstr("cm", NULL), 0, key->line_max));
	else if (key->max_y)
		ft_putstr(tgoto(tgetstr("cm", NULL), 0, key->max_y));
	else if (key->line)
		ft_putstr(tgoto(tgetstr("cm", NULL), key->first_x, key->first_y));
	ft_putchar('\n');
	ft_memdel(&key->line);
	free(key);
	return (line);
}

int				we_have_signal(int permission)
{
	static int past;

	if (permission == 3)
		past = 0;
	else if (permission)
		past = permission;
	return (past);
}

char			*ft_readline(char *p)
{
	t_key		*k;
	static int	zero;
	static int	first;

	k = all(NULL, first++, 1, p);
	key_last_modification(k);
	signal(SIGINT, lance_signal);
	while (1)
	{
		k = keybord_active(k);
		if (we_have_signal(0) || (k->perm_read && (k->entre || (k->ctrl_d
			&& !k->line && ft_strcmp("quote>", p) &&
			ft_strcmp("dquote>", p) && ft_strcmp("> ", p)))))
		{
			zero = 0;
			k->mode = out(k->mode, k);
			return (exit_readline(k, k->mode));
		}
		else if (k->perm_read)
			generateur(k, zero);
		if (k->perm_read)
			k = key_last_modification(NULL);
		zero++;
	}
	return (NULL);
}
