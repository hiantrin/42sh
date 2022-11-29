/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctr_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 08:12:52 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/02 19:51:38 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					sig_winch(int sig)
{
	(void)sig;
	ft_goto(g_pos.x, g_pos.y - 1);
	tputs(tgetstr("cd", NULL), 0, ft_putsfd);
	ft_srl_print(g_l.str, g_prp);
}

void					ft_sig_cnt(int sig)
{
	sig = 1;
	sig_winch(1);
}

void					sig_c(int sig)
{
	struct termios		config;
	struct termios		def;
	int					fd;

	fd = open("/dev/tty", O_RDWR);
	(void)sig;
	tcgetattr(fd, &def);
	tcgetattr(fd, &config);
	ft_strclr(g_l.str);
	g_l.i = 0;
	if (ft_strcmp(g_prp, "(42sh)$> "))
		g_ctr_c = -1;
	ft_putstr("\n(42sh)$> ");
	config.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(fd, TCSANOW, &config);
	tputs(tgetstr("cd", NULL), 0, ft_putsfd);
	get_cur_position();
	tcsetattr(fd, TCSANOW, &def);
	ioctl(0, TIOCSTI, "");
	close(fd);
}
