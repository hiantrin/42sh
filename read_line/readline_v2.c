/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:42:19 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/15 16:35:11 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				out(int mode, t_key *key)
{
	if (we_have_signal(0))
	{
		we_have_signal(3);
		mode = 3;
		return (mode);
	}
	if (key->perm_read && (key->entre || key->ctrl_d))
	{
		mode = key->ctrl_d ? 1 : 0;
		return (mode);
	}
	return (-1);
}

t_key			*key_last_modification(t_key *key)
{
	static t_key	*history;

	if (key)
		history = key;
	return (history);
}

void			manger_error(void)
{
	char *term_type;

	term_type = getenv("TERM");
	if (!term_type)
	{
		ft_putstr(" ⛔️ \x1b[31m \x1b[1m Specify a terminal");
		ft_putendl(" type with `setenv TERM <yourtype>'.\033[0m");
		exit(0);
	}
	else if (tgetent(NULL, term_type) != 1)
	{
		ft_putendl(" ⛔️ \x1b[31m \x1b[1m Terminal type is not defined.\033[0m");
		exit(0);
	}
}

void			change_configuration_term(int mode)
{
	struct termios config;

	if (mode == 1)
	{
		tcgetattr(0, &config);
		config.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(0, 0, &config);
		return ;
	}
	tcgetattr(0, &config);
	config.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, 0, &config);
}

void			generateur(t_key *k, int per)
{
	if (k->alt_c && k->line)
		mode_copy(k);
	else if (k->left && k->line)
		cursor_le(k);
	else if (k->right && k->line)
		cursor_r(k);
	else if (k->delete)
		delete_char(k);
	else if ((k->last || k->first) && k->line)
		first_last_line(k);
	else if ((k->alt_left || k->alt_right) && k->line)
		alt_left_right(k);
	else if (k->up || k->down)
		cursor_up_down(k, per);
	else if ((k->alt_up || k->alt_down) && k->line && ft_strchr(k->line, '\n'))
		alt_up_down(k);
	else if (k->perm_aff)
		plus_char(k);
}
