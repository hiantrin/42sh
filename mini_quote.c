/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 01:40:08 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/06 22:17:59 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			ft_filter_2eme(int len, char *cont, int index)
{
	len++;
	while (cont[len])
	{
		if (cont[len] == index)
			return (len);
		len++;
	}
	return (0);
}

char		*read_quote(char *cont, int index)
{
	char	*lire;
	char	*tmp;
	char	*tmp2;

	lire = NULL;
	if (index == 39)
		lire = ft_readline("quote>");
	else
		lire = ft_readline("dquote>");
	if (!lire)
	{
		ft_memdel(&cont);
		return (NULL);
	}
	tmp = ft_strjoin(cont, "\n");
	tmp2 = ft_strjoin(tmp, lire);
	free(cont);
	ft_memdel(&tmp);
	ft_memdel(&lire);
	return (tmp2);
}

char		*ft_filter_quote(int i, char *cont)
{
	int		resul;
	int		c;
	int		len;

	c = 0;
	len = 0;
	resul = 0;
	i = 0;
	while (cont[len])
	{
		if (cont[len] == 34 || cont[len] == 39)
		{
			c = ((int)cont[len]);
			if ((resul = ft_filter_2eme(len, cont, c)) == 0)
				cont = read_quote(cont, c);
			if (!cont)
				return (NULL);
			len = -1;
			if (resul != 0)
				len = resul;
		}
		len++;
	}
	return (cont);
}
