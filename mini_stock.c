/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_stock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 02:39:34 by szakaria          #+#    #+#             */
/*   Updated: 2020/01/17 12:49:34 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			quote2eme(int len, char *cont, int index)
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

int			ft_deuxv2(char *cont, int i)
{
	while (cont[i] && cont[i] != ' ' && cont[i] != '\t')
	{
		if (cont[i] == 34 || cont[i] == 39)
			i = quote2eme(i, cont, ((int)cont[i]));
		i++;
	}
	return (i);
}

char		**ft_deux(char *cont, char **argv)
{
	int		past;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (cont[i])
	{
		if (i == 0)
			while (cont[i] && (cont[i] == ' ' || cont[i] == '\t'))
				i++;
		past = i;
		if (cont[i] && cont[i] != ' ' && cont[i] != '\t')
			i = ft_deuxv2(cont, i);
		if (cont[i] == ' ' || cont[i] == '\t' || cont[i] == '\0')
		{
			argv[j++] = ft_strsub(cont, past, (i - past));
			while (cont[i] && (cont[i] == ' ' || cont[i] == '\t'))
				i++;
		}
		else
			i++;
	}
	return (argv);
}

int			ft_number_words(char *cont)
{
	int past;
	int i;
	int nb;

	nb = 0;
	i = -1;
	while (cont[++i])
	{
		if (i == 0)
			while (cont[i] && (cont[i] == ' ' || cont[i] == '\t'))
				i++;
		past = i;
		if (cont[i] == 34 || cont[i] == 39)
			i = quote2eme(i, cont, ((int)cont[i]));
		if (past + 1 == i && cont[i + 1] == '\0')
			nb++;
		if ((cont[i + 1] == ' ' || cont[i + 1] == '\t' || cont[i + 1] == '\0')
				&& past != i - 1)
		{
			nb++;
			while (cont[i + 1] && (cont[i + 1] == ' ' || cont[i + 1] == '\t'))
				i++;
		}
	}
	return (nb);
}
