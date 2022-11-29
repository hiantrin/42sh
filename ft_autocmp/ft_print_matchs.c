/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matchs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:13:28 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/02 04:15:40 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

int						ft_read_keys_and_print_matchs(t_dlist *matchs)
{
	int					index;
	int					r;
	int					nb_nodes;

	index = -1;
	r = 0;
	nb_nodes = ft_count_list_nodes(matchs);
	if (nb_nodes > 1)
		while (read(0, &r, sizeof(int)) > 0)
		{
			if (r == LEFT && index == 0)
				index = nb_nodes - 1;
			else if ((r == RIGHT || r == 9) && index == nb_nodes - 1)
				index = 0;
			else if (r == LEFT && index > 0)
				index--;
			else if ((r == RIGHT || r == 9) && index < nb_nodes - 1)
				index++;
			else if (r == ENTR)
				return (index);
			else
				return (-1);
			ft_print_matchs(matchs, index);
		}
	return (0);
}

int						ft_count_list_nodes(t_dlist *matchs)
{
	int					nb;

	nb = 0;
	while (matchs && matchs->next)
	{
		matchs = matchs->next;
		nb++;
	}
	return (nb);
}

static int				ft_get_max_lent(t_dlist *match)
{
	int					maxlent;

	maxlent = 0;
	while (match)
	{
		if (maxlent < (int)ft_strlen(match->data))
			maxlent = ft_strlen(match->data);
		match = match->next;
	}
	return (maxlent);
}

void					ft_print_select(char *str, int index, int select)
{
	if (index == select)
		ft_put4str(tgetstr("us", NULL), "\033[7m", str, "\033[0m");
	else
		ft_putstr(str);
}

void					ft_print_matchs(t_dlist *match, int index)
{
	int					i;
	int					j;
	int					maxlent;
	struct winsize		w;
	int					select;

	select = 0;
	ioctl(1, TIOCGWINSZ, &w);
	i = 0;
	j = g_pos.y;
	maxlent = ft_get_max_lent(match);
	while (match && w.ws_row > j)
	{
		if ((i + maxlent) > w.ws_col)
		{
			i = 0;
			j++;
		}
		tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
		ft_print_select(match->data, index, select);
		i = i + maxlent + 1;
		match = match->next;
		select++;
	}
	tputs(tgoto(tgetstr("cm", NULL), i, j + 1), 0, ft_putsfd);
}
