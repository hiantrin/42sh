/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_keybord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakaria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 23:25:21 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/04 23:27:56 by szakaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_key			*keybord_deactive(t_key *key)
{
	key->ctrl_d = 0;
	key->alt_c = 0;
	key->alt_x = 0;
	key->alt_v = 0;
	key->alt_left = 0;
	key->alt_right = 0;
	key->alt_up = 0;
	key->alt_down = 0;
	key->perm_read = 0;
	key->perm_aff = 0;
	key->up = 0;
	key->down = 0;
	key->left = 0;
	key->right = 0;
	key->last = 0;
	key->first = 0;
	key->entre = 0;
	key->delete = 0;
	key->lastread = NULL;
	return (key);
}

t_key			*active2(t_key *key, long valeur, int len)
{
	len = 0;
	if (valeur == ALT_UP || valeur == ALT_LEFT ||
			valeur == ALT_RIGHT || valeur == ALT_DOWN)
	{
		key->alt_up = ALT_UP == valeur ? 1 : 0;
		key->alt_down = ALT_DOWN == valeur ? 1 : 0;
		key->alt_left = ALT_LEFT == valeur ? 1 : 0;
		key->alt_right = ALT_RIGHT == valeur ? 1 : 0;
		key->perm_read = 1;
	}
	else if (valeur == ALT_C || valeur == ALT_X || valeur == ALT_V)
	{
		key->alt_c = ALT_C == valeur ? 1 : 0;
		key->alt_x = ALT_X == valeur ? 1 : 0;
		key->alt_v = ALT_V == valeur ? 1 : 0;
		key->perm_read = 1;
	}
	else
		return (NULL);
	return (key);
}

t_key			*active(t_key *key, long valeur, int len)
{
	len = 0;
	if (valeur == ENTRE || valeur == DELETE || valeur == CTR_D)
	{
		key->ctrl_d = CTR_D == valeur ? 1 : 0;
		key->entre = ENTRE == valeur ? 1 : 0;
		key->delete = DELETE == valeur ? 1 : 0;
		key->perm_read = 1;
	}
	else if (valeur == UP || valeur == LEFT || valeur == RIGHT
			|| valeur == DOWN || valeur == FIRST || valeur == LAST)
	{
		key->up = UP == valeur ? 1 : 0;
		key->down = DOWN == valeur ? 1 : 0;
		key->left = LEFT == valeur ? 1 : 0;
		key->right = RIGHT == valeur ? 1 : 0;
		key->last = LAST == valeur ? 1 : 0;
		key->first = FIRST == valeur ? 1 : 0;
		key->perm_read = 1;
	}
	else
		return (NULL);
	return (key);
}

int				check_line_error(char *line)
{
	int i;

	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (!ft_isprint(line[i]) || line[i] == '\e' || line[i] == '\t')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

t_key			*keybord_active(t_key *key)
{
	char	myread[MAX_READ];
	int		valeur;
	int		len;

	len = 0;
	valeur = 0;
	key = keybord_deactive(key);
	ft_bzero(myread, MAX_READ);
	len = read(0, myread, MAX_READ);
	valeur = *((int *)myread);
	if (!active(key, valeur, len) && !active2(key, valeur, len))
	{
		if (check_line_error(myread))
		{
			key->perm_read = 1;
			key->perm_aff = 1;
			key->lastread = ft_strdup(myread);
		}
		return (key);
	}
	if (!active(key, valeur, len))
		key = active2(key, valeur, len);
	else
		key = active(key, valeur, len);
	return (key);
}
