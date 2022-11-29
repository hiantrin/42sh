/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:13:44 by ommadhi           #+#    #+#             */
/*   Updated: 2020/12/01 22:29:37 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strcut(char *str, int from, int to)
{
	char		*newstr;
	int			i;
	int			j;

	i = 0;
	j = from;
	if (!str || to < from)
		return (ft_strnew(0));
	newstr = ft_strnew(to - from + 1);
	while (str[j] && j < to)
	{
		newstr[i] = str[j];
		i++;
		j++;
	}
	return (newstr);
}
