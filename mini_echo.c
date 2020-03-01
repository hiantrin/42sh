/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 01:45:03 by szakaria          #+#    #+#             */
/*   Updated: 2020/02/12 15:57:54 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*return_env_variable(t_my *my)
{
	if (&my->tmp4[0] == '\0')
		ft_memdel(&my->tmp4);
	return (NULL);
}

void	mini_echo(char **argv, t_pi pi)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (pi.pipe[1][1] != 0)
		{
			ft_putstr_fd(argv[i], pi.pipe[1][1]);
			if (argv[i + 1] != NULL)
				ft_putstr_fd(" ", pi.pipe[1][1]);
		}
		i++;
	}
	if (pi.pipe[1][1] != 0)
		ft_putstr_fd("\n", pi.pipe[1][1]);
}
