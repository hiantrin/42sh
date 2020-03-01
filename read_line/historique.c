/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:11:19 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 23:20:36 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void			aff_history_line(t_key *key, int commande)
{
	t_list			*l;

	l = (t_list *)list_past(NULL, 1);
	while (l)
	{
		if (l->nb_com == commande)
		{
			ft_memdel(&key->line);
			key->line = ft_strdup(l->str);
			clean_last_line(key);
			return ;
		}
		l = l->next;
	}
	return ;
}

int				cont_allcommande(t_list *l)
{
	int cont;

	cont = 0;
	while (l)
	{
		cont++;
		l = l->next;
	}
	return (cont);
}

void			cursor_up_down(t_key *key, int zero)
{
	static int	commande;
	t_list		*l;

	l = (t_list *)list_past(NULL, 1);
	key->all_commande = cont_allcommande(l);
	if (!zero)
		commande = key->all_commande;
	if (commande == key->all_commande && key->down)
		return ;
	if (key->down && (commande + 1) == key->all_commande)
	{
		commande++;
		ft_memdel(&key->line);
		key->line = NULL;
		clean_last_line(key);
		return ;
	}
	if (!commande && key->up == 1)
		return ;
	if (key->up == 1)
		commande--;
	else if (key->down == 1 && (commande + 1) != key->all_commande)
		commande++;
	aff_history_line(key, commande);
}
