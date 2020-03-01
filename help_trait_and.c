/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_trait_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiantrin <hiantrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 22:36:57 by hiantrin          #+#    #+#             */
/*   Updated: 2020/03/01 17:42:44 by hiantrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		if_three(char *file2, int out, int type, int ***pipe)
{
	if ((out != 1 && out != -1) || type == 3)
	{
		ft_putstr_fd("42sh: ", pipe[0][2][1]);
		ft_putstr_fd(file2, pipe[0][2][1]);
		ft_putendl_fd(": ambiguous redirect", pipe[0][2][1]);
		return (0);
	}
	else if (type == 2 || type == 4)
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `&'",
				pipe[0][2][1]);
		return (0);
	}
	else if ((out == 1 || out == -1) && type == 1)
	{
		trait_the_type(file2, out, type, &pipe[0]);
		pipe[0][2][1] = pipe[0][1][1];
		return (1);
	}
	return (1);
}

int		if_two(int out, int type, int ***pipe)
{
	if (type == 2 || type == 4)
	{
		ft_putendl_fd("42sh: syntax error near unexpected token `&'",
				pipe[0][2][1]);
		return (0);
	}
	if (out == 0 || (type == 3 && out == -1))
		pipe[0][0][1] = -1;
	if (out == 1 || (type == 1 && out == -1))
		pipe[0][1][1] = -1;
	if (out == 2)
		pipe[0][2][1] = -1;
	if (out > 2 && (type == 1 || type == 3))
		close(out);
	return (1);
}

int		if_four(char *file2, int out, int type, int ***pipe)
{
	if (type == 2 || type == 4)
		return (print_syntax_error(&pipe[0]));
	else if (atoi(file2) != 1 && atoi(file2) != 0 && atoi(file2) != 2)
		return (print_bad_file(file2, &pipe[0]));
	else if (type == 1)
	{
		if (out == 1 || out == -1)
			pipe[0][1][1] = pipe[0][atoi(file2)][1];
		else if (out == 0)
			pipe[0][0][1] = pipe[0][atoi(file2)][1];
		else if (out == 2)
			pipe[0][2][1] = pipe[0][atoi(file2)][1];
	}
	else if (type == 3)
	{
		if (out == 0 || out == -1)
			pipe[0][0][1] = pipe[0][atoi(file2)][1];
		else if (out == 1)
			pipe[0][1][1] = pipe[0][atoi(file2)][1];
		else if (out == 2)
			pipe[0][2][1] = pipe[0][atoi(file2)][1];
	}
	return (1);
}

int		print_bad_file(char *file2, int ***pipe)
{
	ft_putstr_fd("42sh: ", pipe[0][2][1]);
	ft_putstr_fd(file2, pipe[0][2][1]);
	ft_putendl_fd(": bad file descriptor", pipe[0][2][1]);
	return (0);
}

int		print_syntax_error(int ***pipe)
{
	ft_putendl_fd("42sh: syntax error near unexpected token `&'",
			pipe[0][2][1]);
	return (0);
}
