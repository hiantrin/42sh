/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trait_the_and.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 17:09:37 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		trait_the_and(char *file, int out, int type, int ***pipe)
{
	char	*file2;

	file2 = &file[1];
	if (file2[0] == '\0')
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `newline'",
			pipe[0][2][1]);
		return (0);
	}
	else if (file2[0] == '-')
		return (if_two(out, type, &pipe[0]));
	else if (check_number_or_word(file2) == 0)
		return (if_three(file2, out, type, &pipe[0]));
	else
		return (if_four(file2, out, type, &pipe[0]));
	return (1);
}

int		check_number_or_word(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (file[i] < 48 || file[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	free_my_pi(t_pi *pi)
{
	int i;

	if (pi->new)
		free(pi->new);
	i = 0;
	while (i < 3)
	{
		free(pi->pipe[i]);
		i++;
	}
	free(pi->pipe);
	free(pi);
}

int		help_to_take_file(int j, char **file)
{
	int i;

	i = j + 1;
	while (file[0][i] && (file[0][i] == ' ' || file[0][i] == '\t'
		|| file[0][i] == '\n'))
		i++;
	join_with_anything(&file[0], i, j + 1);
	i = j + 1;
	if (file[0][i] == '-')
		return (i + 1);
	while (file[0][i] && file[0][i] != ' ' && file[0][i] != '\t'
		&& file[0][i] != '\n')
		i++;
	return (i);
}

int		print_error_num(char *file, int *error, int *status)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `",
		error[1]);
	ft_putstr_fd(file, error[1]);
	ft_putendl_fd("'", error[1]);
	status[0] = 0;
	return (0);
}
