/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_historique.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:42:55 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/05 18:42:57 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int				len_lastline(char *line)
{
	struct winsize	term;
	int				cont;
	int				i;

	ioctl(1, TIOCGWINSZ, &term);
	cont = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_strrchr((line + i), '\n'))
		{
			while (line[i])
			{
				i++;
				cont++;
			}
			return (cont % term.ws_col);
		}
		i++;
	}
	return (cont);
}

int				cont_newline(char *line)
{
	struct winsize	term;
	int				cont;
	int				big_name;
	int				i;
	int				per;

	ioctl(1, TIOCGWINSZ, &term);
	big_name = 0;
	cont = 0;
	i = 0;
	per = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i + 1] == '\0')
		{
			if (!per++)
				big_name += 6;
			cont += big_name / term.ws_col;
			big_name = 0;
			cont++;
		}
		i++;
		big_name++;
	}
	return (cont - 1);
}

t_list			*list_past(t_list *list, int mode)
{
	static t_list *l;

	if (list)
		l = list;
	if (!mode && l)
		while (l)
		{
			ft_memdel(&l->str);
			free(l);
			l = l->next;
		}
	return (l);
}

t_list			*list_new(int nb_com)
{
	t_list *listnew;

	listnew = malloc(sizeof(t_list));
	listnew->nb_com = nb_com;
	listnew->str = NULL;
	listnew->next = NULL;
	return (listnew);
}

void			save_historique(char *line, int mode)
{
	static int		nb;
	char			*tmp;
	t_list			*f;
	t_list			*l;

	tmp = NULL;
	if (!line || (line && !ft_strlen(line)))
		return ;
	l = (!nb) ? list_new(nb) : (t_list *)list_past(NULL, 1);
	f = l;
	while (f->next)
		f = f->next;
	if (mode == 1)
	{
		if (nb)
		{
			f->next = list_new(nb);
			f = f->next;
		}
		f->str = ft_strdup(line);
		f->nb_com = nb;
	}
	list_past(l, 1);
	nb++;
}
